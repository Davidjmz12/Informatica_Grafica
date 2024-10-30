add_subdirectory(geometry)
add_subdirectory(spatial_element)
add_subdirectory(global_config)
add_subdirectory(properties)
add_subdirectory(files)
add_subdirectory(color)
add_subdirectory(scene)

# ------------------------------------------------------------------------------
# Main executable
add_executable(main main.cpp)
target_link_libraries(main PUBLIC scene_file)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(main PUBLIC ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")

add_executable(testing testing.cpp)
target_link_libraries(testing PUBLIC spectral_color)
target_include_directories(testing PUBLIC ${CMAKE_SOURCE_DIR}/include)