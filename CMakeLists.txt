cmake_minimum_required(VERSION 3.30.5)
project(BASICCPPCompiler)
set(CMAKE_CXX_STANDARD 23)

include_directories(lib)
include_directories(lib/lexer)
include_directories(lib/token)
include_directories(lib/parser)
include_directories(lib/emitter)

add_executable(${PROJECT_NAME}
        src/main.cpp
)

add_library(token
        lib/token/token.cpp
        lib/token/token.h
        lib/token/token_type.cpp
        lib/token/token_type.h
)

add_library(lexer
        lib/lexer/lexer.cpp
        lib/lexer/lexer.h
)

add_library(parser
        lib/parser/parser.cpp
        lib/parser/parser.h
)

add_library(emitter
        lib/emitter/emitter.cpp
        lib/emitter/emitter.h
)

target_link_libraries(${PROJECT_NAME} token lexer emitter parser)
