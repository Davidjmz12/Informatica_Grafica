add_subdirectory(geometry)
add_subdirectory(spatial_element)
add_subdirectory(global_config)
add_subdirectory(brdf)
add_subdirectory(files)
add_subdirectory(color)
add_subdirectory(scene)
add_subdirectory(intersection)
add_subdirectory(light)
add_subdirectory(render)
add_subdirectory(kernel_density)

# ------------------------------------------------------------------------------
# Main executable
add_executable(main main.cpp)
target_link_libraries(main PUBLIC scene_file)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(main PUBLIC ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")

add_executable(testing_ testing.cpp)
target_link_libraries(testing_ PUBLIC brdf)
target_include_directories(testing_ PUBLIC ${CMAKE_SOURCE_DIR}/include)