
add_library(brdf brdf.cpp)
target_link_libraries(brdf PUBLIC spectral_color intersection_object ray)
target_include_directories(brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(diffuse_brdf diffuse_brdf.cpp)
target_link_libraries(diffuse_brdf PUBLIC brdf)
target_include_directories(diffuse_brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(refractive_brdf refractive_brdf.cpp)
target_link_libraries(refractive_brdf PUBLIC brdf base)
target_include_directories(refractive_brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(specular_brdf specular_brdf.cpp)
target_link_libraries(specular_brdf PUBLIC brdf)
target_include_directories(specular_brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)
