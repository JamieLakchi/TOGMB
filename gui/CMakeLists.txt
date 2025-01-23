cmake_minimum_required(VERSION 3.22)
project(GUI)
set(CMAKE_AUTOMOC ON)

set(CMAKE_VERBOSE_MAKEFILE ON)
find_package(
  Qt5
  COMPONENTS Widgets
  REQUIRED)

add_library(gui STATIC base.cpp keyboardWindow.cpp functionWindow.cpp
                       variableWindow.cpp menu.cpp)
target_include_directories(gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                      ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(gui PUBLIC calculator Qt5::Widgets)
target_compile_options(gui PRIVATE "-O3")
