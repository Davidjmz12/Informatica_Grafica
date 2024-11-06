add_library(ray ray.cpp)
target_link_libraries(ray PUBLIC vector point)
target_include_directories(ray PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(scene scene.cpp)
target_link_libraries(scene PUBLIC camera light)
target_include_directories(scene PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(camera camera.cpp)
target_link_libraries(camera PUBLIC base)
target_include_directories(camera PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(render render.cpp)
target_link_libraries(render PUBLIC scene global_config color_map)
target_include_directories(render PUBLIC ${CMAKE_SOURCE_DIR}/include)