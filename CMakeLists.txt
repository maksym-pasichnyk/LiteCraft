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

file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_executable("${PROJECT_NAME}" "${SRC_FILES}")

target_include_directories("${PROJECT_NAME}" PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/physfs/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/json/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/range-v3/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/promise.hpp/headers"
)
target_compile_definitions("${PROJECT_NAME}" PRIVATE
    -DGLFW_INCLUDE_NONE
    -DIMGUI_DEFINE_MATH_OPERATORS
    -DGLM_FORCE_XYZW_ONLY
    -DNOMINMAX
)

target_link_libraries("${PROJECT_NAME}" PRIVATE
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
)

target_link_libraries("${PROJECT_NAME}" PRIVATE WS2_32)