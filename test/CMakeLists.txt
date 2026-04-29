include(CTest)

function(add_test_executable target_name)
  add_executable(${target_name} ${ARGN})
  # You can link your lib in here.
  # target_link_libraries(${target_name} PRIVATE mylib)
endfunction()

function(add_ctest_executable target_name)
  add_executable(${target_name} ${ARGN})
  # You can link your lib in here.
  # target_link_libraries(${target_name} PRIVATE mylib)
  add_test(NAME ${target_name} COMMAND ${target_name})
endfunction()

add_ctest_executable(test test.cpp)
add_ctest_executable(test_base62 test_base62.cpp)
add_ctest_executable(test_base64 test_base64.cpp)
