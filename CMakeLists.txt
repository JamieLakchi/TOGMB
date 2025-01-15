cmake_minimum_required(VERSION 3.22)
project(MBTOG)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_library(common_headers INTERFACE)
target_include_directories(common_headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(rats)
add_subdirectory(calculator)

add_executable(MAIN main.cpp)
target_link_libraries(MAIN PRIVATE calculator)
target_compile_options(MAIN PRIVATE "-g3")
