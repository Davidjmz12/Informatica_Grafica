add_library(cone_density cone_density.cpp)
target_include_directories(cone_density PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(constant_density constant_density.cpp)
target_include_directories(constant_density PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(gauss_density gauss_density.cpp)
target_include_directories(gauss_density PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(kernel_density INTERFACE)
target_link_libraries(kernel_density INTERFACE cone_density constant_density gauss_density)