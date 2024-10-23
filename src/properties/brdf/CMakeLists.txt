add_library(brdf brdf.cpp)
target_link_libraries(brdf PUBLIC color point vector)
target_include_directories(brdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

