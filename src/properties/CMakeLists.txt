add_subdirectory(brdf)

add_library(property property.cpp)
target_link_libraries(property PUBLIC spectral_color diffuse_brdf)
target_include_directories(property PUBLIC ${CMAKE_SOURCE_DIR}/include)
