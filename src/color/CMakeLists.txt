add_subdirectory(tone_mapping)

add_library(colorRGB colorRGB.cpp)
target_include_directories(colorRGB PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(spectral_color spectral_color.cpp)
target_link_libraries(spectral_color PUBLIC colorRGB)
target_include_directories(spectral_color PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(color_map color_map.cpp)
target_link_libraries(color_map PUBLIC spectral_color)
target_include_directories(color_map PUBLIC ${CMAKE_SOURCE_DIR}/include)



