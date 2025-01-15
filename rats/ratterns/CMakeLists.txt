cmake_minimum_required(VERSION 3.22)
project(PACKRATPARSER)

add_library(
  ratterns STATIC
  ratterns.cpp
  literalPattern.cpp
  rankedChoicePattern.cpp
  repeaterPattern.cpp
  sequencePattern.cpp
  variablePattern.cpp
  namedPattern.cpp
  numberPattern.cpp
  pattern.cpp)

target_include_directories(
  ratterns PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/..
                  ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_link_libraries(ratterns PUBLIC common_headers)
target_compile_options(ratterns PRIVATE "-O3")
