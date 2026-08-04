cmake_minimum_required(VERSION 3.20)
project(CroissanTUI LANGUAGES CXX)

file(GLOB_RECURSE CROISSANTUI_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h")
file(GLOB_RECURSE CROISSANTUI_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")

add_library(CroissanTUI STATIC ${CROISSANTUI_HEADERS} ${CROISSANTUI_SOURCES})

set_target_properties(CroissanTUI PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Binaries/${CMAKE_SYSTEM_NAME}-x64/$<CONFIG>/CroissanTUI"
)

target_include_directories(CroissanTUI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source")

target_compile_definitions(CroissanTUI PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
    $<$<CONFIG:Dist>:DIST>
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source" PREFIX "Header Files" FILES ${CROISSANTUI_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source" PREFIX "Source Files" FILES ${CROISSANTUI_SOURCES})

# Generate the single-header distribution as a proper build step with a real
# OUTPUT, so targets that include it can depend on it explicitly instead of
# relying on PRE_BUILD ordering (which isn't guaranteed on non-VS generators).
find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(CROISSANTUI_GENERATED_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/Include/ctui_c.h")

add_custom_command(
    OUTPUT "${CROISSANTUI_GENERATED_HEADER}"
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/Scripts/generate_header.py"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS ${CROISSANTUI_HEADERS} ${CROISSANTUI_SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/Scripts/generate_header.py"
    COMMENT "Generating single header"
)

add_custom_target(CroissanTUI_GenerateHeader ALL DEPENDS "${CROISSANTUI_GENERATED_HEADER}")
add_dependencies(CroissanTUI CroissanTUI_GenerateHeader)
