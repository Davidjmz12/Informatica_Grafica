add_library(brdf_lib INTERFACE)
target_link_libraries(brdf_lib INTERFACE diffuse_brdf refractive_brdf specular_brdf roulette_brdf absorption_brdf)

add_library(brdf brdf.cpp)
target_link_libraries(brdf PUBLIC spectral_color ray base)
target_include_directories(brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(diffuse_brdf diffuse_brdf.cpp)
target_link_libraries(diffuse_brdf PUBLIC brdf)
target_include_directories(diffuse_brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(refractive_brdf refractive_brdf.cpp)
target_link_libraries(refractive_brdf PUBLIC brdf)
target_include_directories(refractive_brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(specular_brdf specular_brdf.cpp)
target_link_libraries(specular_brdf PUBLIC brdf)
target_include_directories(specular_brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(roulette_brdf roulette_brdf.cpp)
target_link_libraries(roulette_brdf PUBLIC brdf)
target_include_directories(roulette_brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(absorption_brdf absorption_brdf.cpp)
target_link_libraries(absorption_brdf PUBLIC brdf)
target_include_directories(absorption_brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)
