cmake_minimum_required(VERSION 3.15)

project(CroissanTUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================
# Python generator
# =========================

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(GENERATED_HEADER
    ${CMAKE_SOURCE_DIR}/CroissanTUI/include/ctui_c.h
)

add_custom_command(
    OUTPUT ${GENERATED_HEADER}
    COMMAND Python3::Interpreter
            ${CMAKE_SOURCE_DIR}/CroissanTUI/generate_header.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/CroissanTUI
    DEPENDS ${CMAKE_SOURCE_DIR}/CroissanTUI/generate_header.py
    COMMENT "Generating ctui_c.h"
)

add_custom_target(generate_ctui_header
    DEPENDS ${GENERATED_HEADER}
)

# =========================
# CroissanTUI library
# =========================

file(GLOB_RECURSE CROISSANTUI_SRC
    ${CMAKE_SOURCE_DIR}/CroissanTUI/src/*.cpp
)

add_library(croissantui STATIC ${CROISSANTUI_SRC})

add_dependencies(croissantui generate_ctui_header)

target_include_directories(croissantui
    PUBLIC
        ${CMAKE_SOURCE_DIR}/CroissanTUI/include
        ${CMAKE_SOURCE_DIR}/CroissanTUI/src
)

# =========================
# Sandbox executable
# =========================

add_executable(sandbox
    Sandbox/Main.cpp
)

target_link_libraries(sandbox
    PRIVATE croissantui
)

target_include_directories(sandbox
    PRIVATE
        ${CMAKE_SOURCE_DIR}/CroissanTUI/include
        ${CMAKE_SOURCE_DIR}/CroissanTUI/src
)