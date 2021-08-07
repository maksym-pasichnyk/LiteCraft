cmake_minimum_required(VERSION 3.15)
project(minecraft)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_USE_SCHANNEL ON)

set(BUILD_SHARED_LIBS OFF)
set(PHYSFS_BUILD_SHARED FALSE)

execute_process(COMMAND python gl3w_gen.py --root "${PROJECT_BINARY_DIR}/ThirdParty/gl3w" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/gl3w")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/fmt")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glm")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/gl3w")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/curl")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/entt")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/json")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/physfs")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/zlib-ng")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/range-v3")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/promise.hpp")

target_compile_options(fmt PUBLIC /EHsc)

add_library(imgui STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imconfig.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui_internal.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui_draw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui_tables.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui_widgets.cpp"
)

file(GLOB_RECURSE craft_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

set(craft_include_directories
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/physfs/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/json/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/range-v3/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/promise.hpp/headers"
)
set(craft_compile_definitions
    -DGLFW_INCLUDE_NONE
    -DIMGUI_DEFINE_MATH_OPERATORS
    -DGLM_FORCE_XYZW_ONLY
    -DNOMINMAX
)
set(craft_link_libraries
    glm
    fmt
    EnTT
    glfw
    gl3w
    imgui
    libcurl
    zlibstatic
    promise.hpp
    nlohmann_json
    physfs-static
    WS2_32
)

add_executable("${PROJECT_NAME}-server" "${craft_source_files}")
add_executable("${PROJECT_NAME}-client" "${craft_source_files}")

target_include_directories("${PROJECT_NAME}-client" PRIVATE ${craft_include_directories})
target_include_directories("${PROJECT_NAME}-server" PRIVATE ${craft_include_directories})

target_compile_definitions("${PROJECT_NAME}-client" PRIVATE ${craft_compile_definitions})
target_compile_definitions("${PROJECT_NAME}-server" PRIVATE ${craft_compile_definitions} -DDEDICATED_SERVER)

target_link_libraries("${PROJECT_NAME}-client" PRIVATE ${craft_link_libraries})
target_link_libraries("${PROJECT_NAME}-server" PRIVATE ${craft_link_libraries})
