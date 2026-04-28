### install include ###
# install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/lib1 DESTINATION include)
# install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/lib2 DESTINATION include)
install(FILES
  ${CMAKE_SOURCE_DIR}/include/base.hpp
  DESTINATION include
)

### install lib ###
# install(TARGETS target1 DESTINATION lib)

### install bin ###
# install(TARGETS target2 DESTINATION bin)
