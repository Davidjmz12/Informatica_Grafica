

add_library(clamping clamping.cpp)
target_include_directories(clamping PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_library(drago drago.cpp)
target_include_directories(drago PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_library(equalization equalization.cpp)
target_include_directories(equalization PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(gamma gamma.cpp)
target_include_directories(gamma PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(logarithmic logarithmic.cpp)
target_include_directories(logarithmic PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_library(tone_mapping_lib INTERFACE)
target_link_libraries(tone_mapping_lib INTERFACE clamping drago equalization gamma logarithmic)


# Include directories


