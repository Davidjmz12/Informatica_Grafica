add_library(area_light_lib area_light.cpp)
target_link_libraries(area_light_lib PUBLIC spectral_color intersection_light ray)
target_include_directories(area_light_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
