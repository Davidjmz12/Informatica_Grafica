cmake_minimum_required(VERSION 3.16)
project(GraphicsLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ffast-math")

include(CTest)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)
set(DCMAKE_EXPORT_COMPILE_COMMANDS 1)
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})
add_definitions(-DPROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")
#add_definitions(-DSPECTRAL_COLOR)
#add_definitions(-DMETRICS)
add_subdirectory(src)
add_subdirectory(tests)

include_directories(${CMAKE_SOURCE_DIR}/include)