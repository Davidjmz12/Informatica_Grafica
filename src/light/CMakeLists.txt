add_subdirectory(area_light)

add_library(light light.cpp)
target_link_libraries(light PUBLIC kd-tree)
target_include_directories(light PUBLIC ${CMAKE_SOURCE_DIR}/include)
