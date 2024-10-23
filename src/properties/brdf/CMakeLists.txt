add_library(brdf brdf.cpp)
target_link_libraries(brdf PUBLIC color point vector)
target_include_directories(brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(diffuse_brdf diffuse_brdf.cpp)
target_link_libraries(diffuse_brdf PUBLIC brdf)
target_include_directories(diffuse_brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

