
# Libraries
add_library(tone_mapping tone_mapping.cpp)

add_library(clamping clamping.cpp)
target_link_libraries(clamping PUBLIC tone_mapping)

add_library(drago drago.cpp)
target_link_libraries(drago PUBLIC tone_mapping)

add_library(equalization_clamping equalization_clamping.cpp)
target_link_libraries(equalization_clamping PUBLIC tone_mapping)

add_library(equalization equalization.cpp)
target_link_libraries(equalization PUBLIC tone_mapping)

add_library(gamma_clamping gamma_clamping.cpp)
target_link_libraries(gamma_clamping PUBLIC tone_mapping)

add_library(gamma gamma.cpp)
target_link_libraries(gamma PUBLIC tone_mapping)

add_library(logarithmic logarithmic.cpp)
target_link_libraries(logarithmic PUBLIC tone_mapping)


add_library(tone_mapping_lib INTERFACE)
target_link_libraries(tone_mapping_lib INTERFACE tone_mapping clamping drago equalization_clamping equalization gamma_clamping gamma logarithmic)


# Include directories

target_include_directories(tone_mapping PUBLIC ${CMAKE_SOURCE_DIR}/include)


