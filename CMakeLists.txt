cmake_minimum_required(VERSION 3.21)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

project(Thermite_Lang LANGUAGES CXX)

set(THERMITE_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories(${THERMITE_SRC_INCLUDE_DIR})

add_subdirectory ("src/")