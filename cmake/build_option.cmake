########################################
# Option and Cache Var
set(MY_LIBRARY_TYPE "STATIC" CACHE STRING "STATIC | SHARED")
option(MY_POSITION_INDEPENDENT_CODE "Is use -fPIC to compile code." ON)
option(MY_BUILD_TEST "Is build test codes" OFF)
option(MY_BUILD_EXAMPLE "Is build test codes" OFF)
########################################

# Message for Debug
message(STATUS "MY_LIBRARY_TYPE: ${MY_LIBRARY_TYPE}")
message(STATUS "MY_POSITION_INDEPENDENT_CODE: ${MY_POSITION_INDEPENDENT_CODE}")

# Settings depends options above
set(CMAKE_POSITION_INDEPENDENT_CODE ${MY_POSITION_INDEPENDENT_CODE})

