cmake_minimum_required(VERSION 3.15)
project(CroissanTUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CROISSANTUI_SRC
    "CroissanTUI/src/*.cpp"
)

add_library(croissantui ${CROISSANTUI_SRC})

target_include_directories(croissantui
    PUBLIC
        CroissanTUI/src
)

add_executable(sandbox
    Sandbox/Main.cpp
)

target_link_libraries(sandbox
    PRIVATE croissantui
)