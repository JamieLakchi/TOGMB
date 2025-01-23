# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "gui\\CMakeFiles\\gui_autogen.dir\\AutogenUsed.txt"
  "gui\\CMakeFiles\\gui_autogen.dir\\ParseCache.txt"
  "gui\\gui_autogen"
  )
endif()
