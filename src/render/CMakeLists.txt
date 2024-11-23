add_subdirectory(photon_mapping)

add_library(render render.cpp)
target_link_libraries(render PUBLIC scene color_map intersection_object)
target_include_directories(render PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(ray_tracing ray_tracing.cpp)
target_link_libraries(ray_tracing PUBLIC render)
target_include_directories(ray_tracing PUBLIC ${CMAKE_SOURCE_DIR}/include)