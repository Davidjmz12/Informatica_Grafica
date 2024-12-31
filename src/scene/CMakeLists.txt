add_library(ray ray.cpp)
target_link_libraries(ray PUBLIC vector point)
target_include_directories(ray PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(scene scene.cpp)
target_link_libraries(scene PUBLIC camera light area_light_lib)
target_include_directories(scene PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(camera camera.cpp)
target_link_libraries(camera PUBLIC base)
target_include_directories(camera PUBLIC ${CMAKE_SOURCE_DIR}/include)
