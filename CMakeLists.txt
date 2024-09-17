cmake_minimum_required(VERSION 3.16)
project(GraphicsLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include(CTest)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)
add_subdirectory(tests)

include_directories(${CMAKE_SOURCE_DIR}/include)