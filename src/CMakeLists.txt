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

add_library(conection conection.cpp)
target_link_libraries(conection PUBLIC sphere)


# Include directories
target_include_directories(base PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(conection PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(geometric PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(linear_map PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(matrix PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(sphere PUBLIC ${CMAKE_SOURCE_DIR}/include)