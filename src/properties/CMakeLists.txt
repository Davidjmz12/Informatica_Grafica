add_subdirectory(brdf)

add_library(property property.cpp)
target_link_libraries(property PUBLIC color)
target_include_directories(property PUBLIC ${CMAKE_SOURCE_DIR}/include)
