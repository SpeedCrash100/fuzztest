fuzztest_common_logging_dep = declare_dependency(
    include_directories: '..',
    dependencies: [absl_log],
)

fuzztest_defs_dep = declare_dependency(
    include_directories: '..',
    dependencies: [absl_span],
)

fuzztest_hash = static_library('fuzztest_hash', 'hash.cc', dependencies: [fuzztest_defs_dep])
fuzztest_hash_dep = declare_dependency(
    include_directories: '..',
    dependencies: [fuzztest_defs_dep],
    link_with: [fuzztest_hash],
    link_args: ['-Wl,-Bstatic', '-lcrypto', '-Wl,-Bdynamic', '-ldl'],
)

fuzztest_remote_file = static_library(
    'fuzztest_remote_file',
    ['remote_file.cc', 'remote_file_oss.cc'],
    cpp_args: ['-DCENTIPEDE_DISABLE_RIEGELI'],
    dependencies: [fuzztest_common_logging_dep, fuzztest_defs_dep, absl_log],
)

fuzztest_remote_file_dep = declare_dependency(
    include_directories: '..',
    dependencies: [fuzztest_common_logging_dep, fuzztest_defs_dep, absl_log],
    link_with: [fuzztest_remote_file],
)

fuzztest_blob_file = static_library(
    'fuzztest_blob_file',
    'blob_file.cc',
    cpp_args: '-DCENTIPEDE_DISABLE_RIEGELI',

    dependencies: [
        fuzztest_common_logging_dep,
        fuzztest_defs_dep,
        fuzztest_hash_dep,
        fuzztest_remote_file_dep,
        absl_log,
        absl_status,
        absl_strings,
        absl_time,
    ],
)

fuzztest_blob_file_dep = declare_dependency(
    include_directories: '..',
    dependencies: [
        fuzztest_common_logging_dep,
        fuzztest_defs_dep,
        fuzztest_hash_dep,
        fuzztest_remote_file_dep,
        absl_log,
        absl_status,
        absl_strings,
        absl_time,
    ],
    link_with: [fuzztest_blob_file],
)