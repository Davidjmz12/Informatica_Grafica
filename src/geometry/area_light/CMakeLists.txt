add_library(area_light INTERFACE)
target_link_libraries(area_light INTERFACE spectral_color intersection_object ray)

add_library(box_light box_light.cpp)
target_link_libraries(box_light PUBLIC area_light box)
target_include_directories(box_light PUBLIC ${CMAKE_SOURCE_DIR}/include)
