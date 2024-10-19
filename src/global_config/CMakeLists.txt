# Define las bibliotecas individuales
add_library(global_config global_config.cpp)
target_include_directories(global_config PUBLIC ${CMAKE_SOURCE_DIR}/include)
