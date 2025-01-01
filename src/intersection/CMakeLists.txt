add_library(intersection intersection.cpp)
target_link_libraries(intersection PUBLIC ray)
target_include_directories(intersection PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(intersection_object intersection_object.cpp)
target_link_libraries(intersection_object PUBLIC intersection brdf)
target_include_directories(intersection_object PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_library(intersection_light intersection_light.cpp)
target_link_libraries(intersection_light PUBLIC intersection spectral_color)
target_include_directories(intersection_light PUBLIC ${CMAKE_SOURCE_DIR}/include)