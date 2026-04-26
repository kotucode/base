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

### Here is examples ###
# add_test_executable(my_test1 my_test1.cpp)
# add_ctest_executable(my_ctest2 my_ctest2.cpp)


