subdir('grammars')

fuzztest_logging = static_library(
    'fuzztest_logging',
    'internal/logging.cc',
    include_directories: '..',
    dependencies: absl_strings,
)
fuzztest_logging_dep = declare_dependency(
    include_directories: '..',
    link_with: fuzztest_logging,
    dependencies: absl_strings,
)

fuzztest_meta_dep = declare_dependency(
    include_directories: '..',
    dependencies: absl_int128,
)

fuzztest_printer_dep = declare_dependency(
    include_directories: '..',
    dependencies: [fuzztest_meta_dep, absl_str_format],
)

fuzztest_any_dep = declare_dependency(
    include_directories: '..',
    dependencies: [fuzztest_meta_dep, fuzztest_logging_dep],
)

fuzztest_absl_helpers_dep = declare_dependency(
    include_directories: '..',
    dependencies: [fuzztest_logging_dep, absl_time],
)

fuzztest_type_support_dep = declare_dependency(
    include_directories: '..',
    dependencies: [
        fuzztest_absl_helpers_dep,
        fuzztest_meta_dep,
        fuzztest_printer_dep,
        absl_function_ref,
        absl_symbolize,
        absl_int128,
        absl_strings,
        absl_str_format,
        absl_time,
    ],
)

fuzztest_table_of_recent_compares_dep = declare_dependency(
    include_directories: '..',
    dependencies: [
        fuzztest_type_support_dep,
        absl_flat_hash_set,
        absl_random_bit_gen_ref,
        absl_random_distributions,
        absl_strings,
    ],
)

fuzztest_coverage = static_library(
    'fuzztest_coverage',
    'internal/coverage.cc',
    dependencies: [
        fuzztest_logging_dep,
        fuzztest_table_of_recent_compares_dep,
        absl_core_headers,
        absl_str_format,
        absl_span,
        absl_strings,
    ],
)
fuzztest_coverage_dep = declare_dependency(
    include_directories: '..',
    link_with: [fuzztest_coverage],
    dependencies: [
        fuzztest_logging_dep,
        fuzztest_table_of_recent_compares_dep,
        absl_core_headers,
        absl_str_format,
        absl_span,
    ],
)

fuzztest_seed_seq = static_library(
    'fuzztest_seed_seq',
    'internal/seed_seq.cc',
    dependencies: [
        fuzztest_logging_dep,
        absl_random_random,
        absl_strings,
        absl_span,
    ],
)

fuzztest_seed_seq_dep = declare_dependency(
    include_directories: '..',
    link_with: [fuzztest_seed_seq],
    dependencies: [
        fuzztest_logging_dep,
        absl_random_random,
        absl_strings,
        absl_span,
    ],
)

fuzztest_serialization = static_library(
    'fuzztest_serialization',
    'internal/serialization.cc',
    dependencies: [
        fuzztest_meta_dep,
        absl_int128,
        absl_strings,
        absl_str_format,
        absl_span,
    ],
)

fuzztest_serialization_dep = declare_dependency(
    include_directories: '..',
    link_with: [fuzztest_serialization],
    dependencies: [
        fuzztest_meta_dep,
        absl_int128,
        absl_strings,
        absl_str_format,
        absl_span,
    ],
)

fuzztest_status = static_library(
    'fuzztest_status',
    'internal/status.cc',
    include_directories: '..',
    dependencies: [
        absl_status,
        absl_strings,
        absl_cord,
    ],
)

fuzztest_status_dep = declare_dependency(
    include_directories: '..',
    link_with: [fuzztest_status],
    dependencies: [
        absl_status,
        absl_strings,
        absl_cord,
    ],
)

fuzztest_domain_core = static_library(
    'fuzztest_domain_core',
    'internal/domains/domain_base.cc',
    dependencies: [
        fuzztest_absl_helpers_dep,
        fuzztest_any_dep,
        fuzztest_coverage_dep,
        fuzztest_logging_dep,
        fuzztest_meta_dep,
        fuzztest_printer_dep,
        fuzztest_seed_seq_dep,
        fuzztest_serialization_dep,
        fuzztest_status_dep,
        fuzztest_table_of_recent_compares_dep,
        fuzztest_type_support_dep,
        absl_flat_hash_map,
        absl_flat_hash_set,
        absl_function_ref,
        absl_int128,
        absl_random_random,
        absl_random_bit_gen_ref,
        absl_random_distributions,
        absl_status,
        absl_strings,
        absl_str_format,
        absl_time,
        absl_span,
    ],
)

fuzztest_domain_core = declare_dependency(
    include_directories: '..',
    link_with: [fuzztest_domain_core],
    dependencies: [
        fuzztest_absl_helpers_dep,
        fuzztest_any_dep,
        fuzztest_coverage_dep,
        fuzztest_logging_dep,
        fuzztest_meta_dep,
        fuzztest_printer_dep,
        fuzztest_seed_seq_dep,
        fuzztest_serialization_dep,
        fuzztest_status_dep,
        fuzztest_table_of_recent_compares_dep,
        fuzztest_type_support_dep,
        absl_flat_hash_map,
        absl_flat_hash_set,
        absl_function_ref,
        absl_int128,
        absl_random_random,
        absl_random_bit_gen_ref,
        absl_random_distributions,
        absl_status,
        absl_strings,
        absl_str_format,
        absl_time,
        absl_span,
    ],
)