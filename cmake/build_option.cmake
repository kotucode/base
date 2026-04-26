########################################
# Option and Cache Var
set(MY_LIBRARY_TYPE "STATIC" CACHE STRING "STATIC | SHARED")
option(MY_POSITION_INDEPENDENT_CODE "Is use -fPIC to compile code." ON)
########################################

# Message for Debug
message(STATUS "MY_LIBRARY_TYPE: ${MY_LIBRARY_TYPE}")
message(STATUS "MY_POSITION_INDEPENDENT_CODE: ${MY_POSITION_INDEPENDENT_CODE}")

# Settings depends options above
set(CMAKE_POSITION_INDEPENDENT_CODE ${MY_POSITION_INDEPENDENT_CODE})

