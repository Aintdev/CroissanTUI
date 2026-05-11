cmake_minimum_required(VERSION 3.10)
project(CroissanTUI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "CroissanTUI/src/*.cpp")

add_library(croissantui ${SOURCES})
target_include_directories(croissantui PUBLIC CroissanTUI/src/ CroissanTUI/include/)

add_executable(sandbox Sandbox/Main.cpp)
target_link_libraries(sandbox croissantui)
target_include_directories(sandbox PRIVATE CroissanTUI/src/ CroissanTUI/include/)
