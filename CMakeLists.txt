cmake_minimum_required(VERSION 3.16)
project(Base VERSION 1.0.1 LANGUAGES C CXX)

include(cmake/build_option.cmake)
include(cmake/compile_setting.cmake)

add_subdirectory(src)

if(MY_BUILD_EXAMPLE)
  add_subdirectory(example)
endif()

if(MY_BUILD_TEST)
  add_subdirectory(test)
endif()

include(cmake/install.cmake)
include(cmake/cpack.cmake)
