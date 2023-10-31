// Copyright 2022 The Centipede Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "./centipede/workdir.h"

#include <cstddef>
#include <filesystem>  // NOLINT
#include <string>
#include <string_view>
#include <system_error>  // NOLINT
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "./centipede/environment.h"
#include "./centipede/logging.h"

namespace centipede {

namespace {

inline constexpr std::string_view kCorpusShardStem = "corpus";

// If `annotation` is empty, returns an empty string. Otherwise, verifies that
// it does not start with a dot and returns it with a dot prepended.
std::string NormalizeAnnotation(std::string_view annotation) {
  std::string ret;
  if (!annotation.empty()) {
    CHECK_NE(annotation.front(), '.');
    ret = absl::StrCat(".", annotation);
  }
  return ret;
}

}  // namespace

//------------------------------------------------------------------------------
//                             WorkDir::PathInfo

WorkDir::ShardedFileInfo::ShardedFileInfo(std::string_view base_dir,
                                          std::string_view rel_prefix,
                                          size_t my_shard_index)
    : prefix_{std::filesystem::path(base_dir) / rel_prefix},
      my_shard_index_{my_shard_index} {}

std::string WorkDir::ShardedFileInfo::ShardPath(size_t shard_index) const {
  return absl::StrFormat("%s%0*d", prefix_, kDigitsInShardIndex, shard_index);
}

std::string WorkDir::ShardedFileInfo::MyShardPath() const {
  return ShardPath(my_shard_index_);
}

std::string WorkDir::ShardedFileInfo::AllShardsGlob() const {
  return absl::StrCat(prefix_, "*");
}

//------------------------------------------------------------------------------
//                                 WorkDir

WorkDir WorkDir::FromCorpusShardPath(    //
    std::string_view corpus_shard_path,  //
    std::string_view binary_name,        //
    std::string_view binary_hash) {
  const std::filesystem::path path{corpus_shard_path};
  const std::string dir = path.parent_path();
  const std::string stem = path.stem();
  CHECK_EQ(stem, kCorpusShardStem) << VV(corpus_shard_path);
  const std::string dot_ext = path.extension();
  CHECK(!dot_ext.empty() && dot_ext[0] == '.') << VV(corpus_shard_path);
  const std::string ext = dot_ext.substr(1);
  CHECK_EQ(ext.size(), kDigitsInShardIndex) << VV(corpus_shard_path);
  size_t shard_index = -1;
  CHECK(absl::SimpleAtoi(ext, &shard_index)) << VV(corpus_shard_path);
  return WorkDir{
      dir,
      std::string{binary_name},
      std::string{binary_hash},
      shard_index,
  };
}

WorkDir::WorkDir(             //
    std::string workdir,      //
    std::string binary_name,  //
    std::string binary_hash,  //
    size_t my_shard_index)
    : workdir_holder_{std::move(workdir)},
      binary_name_holder_{std::move(binary_name)},
      binary_hash_holder_{std::move(binary_hash)},
      my_shard_index_holder_{my_shard_index},
      workdir_{workdir_holder_},
      binary_name_{binary_name_holder_},
      binary_hash_{binary_hash_holder_},
      my_shard_index_{my_shard_index_holder_} {}

WorkDir::WorkDir(const centipede::Environment& env)
    : workdir_{env.workdir},
      binary_name_{env.binary_name},
      binary_hash_{env.binary_hash},
      my_shard_index_{env.my_shard_index} {}

std::string WorkDir::CoverageDirPath() const {
  return std::filesystem::path(workdir_) /
         absl::StrCat(binary_name_, "-", binary_hash_);
}

std::string WorkDir::CrashReproducerDirPath() const {
  return std::filesystem::path(workdir_) / "crashes";
}

std::string WorkDir::BinaryInfoDirPath() const {
  return std::filesystem::path(CoverageDirPath()) / "binary-info";
}

WorkDir::ShardedFileInfo WorkDir::CorpusFiles() const {
  return {workdir_, absl::StrCat(kCorpusShardStem, "."), my_shard_index_};
}

WorkDir::ShardedFileInfo WorkDir::DistilledCorpusFiles() const {
  return {workdir_, absl::StrCat("distilled-", binary_name_, "."),
          my_shard_index_};
}

WorkDir::ShardedFileInfo WorkDir::FeaturesFiles() const {
  return {CoverageDirPath(), "features.", my_shard_index_};
}

WorkDir::ShardedFileInfo WorkDir::DistilledFeaturesFiles() const {
  return {CoverageDirPath(),
          absl::StrCat("distilled-features-", binary_name_, "."),
          my_shard_index_};
}

std::string WorkDir::CoverageReportPath(std::string_view annotation) const {
  return std::filesystem::path(workdir_) /
         absl::StrFormat("coverage-report-%s.%0*d%s.txt", binary_name_,
                         kDigitsInShardIndex, my_shard_index_,
                         NormalizeAnnotation(annotation));
}

std::string WorkDir::CorpusStatsPath(std::string_view annotation) const {
  return std::filesystem::path(workdir_) /
         absl::StrFormat("corpus-stats-%s.%0*d%s.json", binary_name_,
                         kDigitsInShardIndex, my_shard_index_,
                         NormalizeAnnotation(annotation));
}

std::string WorkDir::FuzzingStatsPath(std::string_view annotation) const {
  return std::filesystem::path(workdir_) /
         absl::StrFormat("fuzzing-stats-%s.%0*d%s.csv", binary_name_,
                         kDigitsInShardIndex, my_shard_index_,
                         NormalizeAnnotation(annotation));
}

std::string WorkDir::SourceBasedCoverageRawProfilePath() const {
  // Pass %m to enable online merge mode: updates file in place instead of
  // replacing it %m is replaced by lprofGetLoadModuleSignature(void) which
  // should be consistent for a fixed binary
  return std::filesystem::path(CoverageDirPath()) /
         absl::StrFormat("clang_coverage.%0*d.%s.profraw", kDigitsInShardIndex,
                         my_shard_index_, "%m");
}

std::string WorkDir::SourceBasedCoverageIndexedProfilePath() const {
  return std::filesystem::path(CoverageDirPath()) /
         absl::StrFormat("clang_coverage.profdata");
}

std::string WorkDir::SourceBasedCoverageReportPath(
    std::string_view annotation) const {
  return std::filesystem::path(workdir_) /
         absl::StrFormat("source-coverage-report-%s.%0*d%s", binary_name_,
                         kDigitsInShardIndex, my_shard_index_,
                         NormalizeAnnotation(annotation));
}

std::string WorkDir::RUsageReportPath(std::string_view annotation) const {
  return std::filesystem::path(workdir_) /
         (absl::StrFormat("rusage-report-%s.%0*d%s.txt", binary_name_,
                          kDigitsInShardIndex, my_shard_index_,
                          NormalizeAnnotation(annotation)));
}

std::vector<std::string> WorkDir::EnumerateRawCoverageProfiles() const {
  // Unfortunately we have to enumerate the profiles from the filesystem since
  // clang-coverage generates its own hash of the binary to avoid collisions
  // between builds. We account for this in Centipede already with the
  // per-binary coverage directory but LLVM coverage (perhaps smartly) doesn't
  // trust the user to get this right. We could call __llvm_profile_get_filename
  // in the runner and plumb it back to us but this is simpler.
  const std::string dir_path = CoverageDirPath();
  std::error_code dir_error;
  const auto dir_iter =
      std::filesystem::directory_iterator(dir_path, dir_error);
  if (dir_error) {
    LOG(ERROR) << "Failed to access coverage dir '" << dir_path
               << "': " << dir_error.message();
    return {};
  }
  std::vector<std::string> raw_profiles;
  for (const auto &entry : dir_iter) {
    if (entry.is_regular_file() && entry.path().extension() == ".profraw")
      raw_profiles.push_back(entry.path());
  }
  return raw_profiles;
}

}  // namespace centipede

