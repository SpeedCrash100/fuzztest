generated_antlr_parser = static_library(
    'generated_antlr_parser',
    files(
        'ANTLRv4Lexer.cpp',
        'ANTLRv4Parser.cpp',
        'ANTLRv4ParserBaseListener.cpp',
        'ANTLRv4ParserListener.cpp',
    ),
    dependencies: antlr4_runtime,
)

generated_antlr_parser_include_dir = include_directories('.')

generated_antlr_parser = declare_dependency(
    include_directories: [generated_antlr_parser_include_dir],
    dependencies: [antlr4_runtime],
)