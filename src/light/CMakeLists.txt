add_subdirectory(area_light)

add_library(light light.cpp)
target_link_libraries(light PUBLIC geometry)
target_include_directories(light PUBLIC ${CMAKE_SOURCE_DIR}/include)
