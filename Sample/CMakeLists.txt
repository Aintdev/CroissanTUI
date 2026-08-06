cmake_minimum_required(VERSION 3.20)
project(Sample LANGUAGES C CXX)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE)

if(MSVC)
    add_compile_options(/EHsc /Zc:preprocessor /Zc:__cplusplus)
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../" "${CMAKE_CURRENT_BINARY_DIR}/CroissanTUI")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT App)

add_subdirectory(App)