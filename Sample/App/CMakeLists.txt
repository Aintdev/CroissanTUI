file(GLOB_RECURSE APP_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h")
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")

add_executable(App ${APP_HEADERS} ${APP_SOURCES})

set_target_properties(App PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Binaries/${CMAKE_SYSTEM_NAME}-x64/$<CONFIG>/App"
)

target_include_directories(App PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Source"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../Include"
)

target_link_libraries(App PRIVATE CroissanTUI)

# Make sure the generated single header exists before App is compiled
add_dependencies(App CroissanTUI_GenerateHeader)

target_compile_definitions(App PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
    $<$<CONFIG:Dist>:DIST>
)

if(WIN32)
    target_compile_definitions(App PRIVATE WINDOWS)
endif()
