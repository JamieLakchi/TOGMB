cmake_minimum_required(VERSION 3.26)
project(GUI)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g3")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(gui
        base.cpp
        keyboardWindow.cpp
        functionWindow.cpp
        variableWindow.cpp)

target_link_libraries(gui Qt5::Widgets)
