
add_library(kd-tree kd-tree.cpp)
target_link_libraries(kd-tree PUBLIC geometry)
target_include_directories(kd-tree PUBLIC ${CMAKE_SOURCE_DIR}/include)
