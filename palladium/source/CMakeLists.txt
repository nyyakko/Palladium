set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(palladium_SourceFiles ${palladium_SourceFiles}
    "${DIR}/main.cpp"
    "${DIR}/palladium.cpp"
    "${DIR}/graphics/elements.cpp"
    "${DIR}/graphics/core/layout.cpp"
    "${DIR}/evaluation/evaluation.cpp"
    "${DIR}/evaluation/lexer.cpp"
    "${DIR}/evaluation/parser.cpp"

    PARENT_SCOPE
)
