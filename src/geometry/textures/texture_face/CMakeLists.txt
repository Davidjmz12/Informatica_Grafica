
add_library(texture_face_ppm texture_face_ppm.cpp)
target_link_libraries(texture_face_ppm PUBLIC ppm_file)
target_include_directories(texture_face_ppm PUBLIC ${CMAKE_SOURCE_DIR}/include)

