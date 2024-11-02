add_library(area_light area_light.cpp)
target_link_libraries(area_light PUBLIC spectral_color intersection_light ray)
target_include_directories(area_light PUBLIC ${CMAKE_SOURCE_DIR}/include)
