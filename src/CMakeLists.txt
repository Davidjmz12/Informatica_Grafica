add_executable(main main.cpp)
target_link_libraries(main PUBLIC linear_map sphere)


# Libraries
add_library(geometric geometric.cpp)

add_library(matrix matrix.cpp)
target_link_libraries(matrix PUBLIC geometric)

add_library(linear_map linear_map.cpp)
target_link_libraries(linear_map PUBLIC base matrix)

add_library(base base.cpp)
target_link_libraries(base PUBLIC matrix linear_map)

add_library(sphere sphere.cpp)
target_link_libraries(sphere PUBLIC base)


# Images
add_library(pixel pixel.cpp)

add_library(pixel_map pixel_map.cpp)
target_link_libraries(pixel_map PUBLIC pixel)

add_library(tone_mapping tone_mapping.cpp)

add_library(ppm_file ppm_file.cpp)
target_link_libraries(ppm_file PUBLIC pixel_map)



# Include directories
target_include_directories(base PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(geometric PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(linear_map PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(matrix PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(sphere PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(pixel PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(pixel_map PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(tone_mapping PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(ppm_file PUBLIC ${CMAKE_SOURCE_DIR}/include)