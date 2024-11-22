
# TEST SPATIAL ELEMENT
add_executable(test_refractive test_refractive.cpp)
target_link_libraries(test_refractive PUBLIC refractive_brdf)
add_test(NAME test_refractive COMMAND test_refractive)
target_include_directories(test_refractive PUBLIC ${CMAKE_SOURCE_DIR}/include)
