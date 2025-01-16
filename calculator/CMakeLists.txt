cmake_minimum_required(VERSION 3.22)
project(CALCULATOR)

add_library(calculator STATIC MathParser.cpp ASTConverter.cpp)

target_include_directories(calculator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                             ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(calculator PUBLIC common_headers packrat)
target_compile_options(calculator PRIVATE "-g3")
