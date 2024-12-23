cmake_minimum_required(VERSION 3.30.5)
project(BASICCPPCompiler)
set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(${PROJECT_NAME}
    main.cpp
)
add_library(lexer
    lexer.cpp
    lexer.h
    token.cpp
    token.h
    token_type.cpp
    token_type.h
)

target_link_libraries(${PROJECT_NAME} lexer)
