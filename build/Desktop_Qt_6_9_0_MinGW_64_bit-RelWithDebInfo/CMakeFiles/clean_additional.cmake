# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "CMakeFiles\\Maltese_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Maltese_autogen.dir\\ParseCache.txt"
  "Maltese_autogen"
  )
endif()
