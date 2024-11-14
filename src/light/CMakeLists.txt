add_subdirectory(area_light)

add_library(light punctual_light.cpp)
target_link_libraries(light PUBLIC kd-tree)
target_include_directories(light PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(photon photon.cpp)
target_link_libraries(photon PUBLIC point vector spectral_color)
target_include_directories(photon PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(collection_light collection_light.cpp)
target_link_libraries(collection_light PUBLIC light)
target_include_directories(collection_light PUBLIC ${CMAKE_SOURCE_DIR}/include)
