project('google-fuzztest', ['c', 'cpp'], meson_version: '>=0.60')

absl_log = dependency('absl', 'absl_log', modules: ['absl::log'])

absl_status = dependency('absl', 'absl_status', modules: ['absl::status'])
absl_strings = dependency('absl', 'absl_strings', modules: ['absl::strings'])
absl_time = dependency('absl', 'absl_time', modules: ['absl::time'])
absl_core_headers = dependency('absl', 'absl_core_headers', modules: ['absl::core_headers'])
absl_flat_hash_set = dependency('absl', 'absl_flat_hash_set', modules: ['absl::flat_hash_set'])
absl_flat_hash_map = dependency('absl', 'absl_flat_hash_map', modules: ['absl::flat_hash_map'])
absl_function_ref = dependency('absl', 'absl_function_ref', modules: ['absl::function_ref'])
absl_int128 = dependency('absl', 'absl_int128', modules: ['absl::int128'])
absl_random_bit_gen_ref = dependency(
    'absl',
    'absl_random_bit_gen_ref',
    modules: ['absl::random_internal::randen'],
)
absl_random_distributions = dependency(
    'absl',
    'absl_random_distributions',
    modules: ['absl::random_distributions'],
)
absl_random_random = dependency('absl', 'absl_random_random', modules: ['absl::random_random'])
absl_span = dependency('absl', 'absl_span', modules: ['absl::types::span'])
absl_str_format = dependency('absl', 'absl_str_format', modules: ['absl::strings_internal::str_format'])
absl_symbolize = dependency('absl', 'absl_symbolize', modules: ['absl::debugging_internal::symbolize'])
absl_cord = dependency('absl', 'absl_cord', modules: ['absl::cord'])

re2 = dependency('re2')

antlr4_runtime = dependency('antlr4-runtime', method: 'cmake', modules: ['antlr4_static'])

subdir('grammar_codegen')
subdir('tools')
subdir('common')
subdir('fuzztest')