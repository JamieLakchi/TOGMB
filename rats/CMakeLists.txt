cmake_minimum_required(VERSION 3.22)
project(PACKRATPARSER)

add_subdirectory(ratterns)

add_library(
  packrat STATIC parserMatchers.cpp parserRatImpl.cpp parseTreeNode.cpp
                 grammarStorage.cpp graphvizTool.cpp)

target_include_directories(packrat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                          ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(packrat PUBLIC ratterns common_headers)
target_compile_options(packrat PRIVATE "-O3")
