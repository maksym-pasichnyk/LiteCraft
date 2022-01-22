cmake_minimum_required(VERSION 3.20)
project(minecraft)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(BUILD_SHARED_LIBS OFF)

add_definitions(
    -DNOMINMAX
    -DGLM_FORCE_INLINE
    -DGLM_FORCE_SWIZZLE
    -DWIN32_LEAN_AND_MEAN
    -DGLM_FORCE_DEPTH_ZERO_TO_ONE
    -DGLM_FORCE_DEFAULT_ALIGNED_GENTYPES
    -D_LIBCPP_ENABLE_CXX20_REMOVED_TYPE_TRAITS
)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_USE_SCHANNEL ON)
endif()

#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/curl")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/entt")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/zlib-ng" "${CMAKE_CURRENT_BINARY_DIR}/zlib_build")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/asyncplusplus")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Blaze")

file(GLOB_RECURSE craft_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

set(craft_include_directories
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_BINARY_DIR}/zlib_build"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/zlib-ng"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/asyncplusplus/include"
)
set(craft_compile_definitions
    -D_USE_MATH_DEFINES
    -DGLFW_INCLUDE_NONE
    -DIMGUI_DEFINE_MATH_OPERATORS
    -DGLM_FORCE_XYZW_ONLY
    -DNOMINMAX
)
set(craft_link_libraries
    EnTT
    zlib
    Async++
    blaze
)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(craft_link_libraries "${craft_link_libraries};WS2_32")
endif()

add_executable("${PROJECT_NAME}-server" "${craft_source_files}")
add_executable("${PROJECT_NAME}-client" "${craft_source_files}")

target_include_directories("${PROJECT_NAME}-client" PRIVATE ${craft_include_directories})
target_include_directories("${PROJECT_NAME}-server" PRIVATE ${craft_include_directories})

target_compile_definitions("${PROJECT_NAME}-client" PRIVATE ${craft_compile_definitions})
target_compile_definitions("${PROJECT_NAME}-server" PRIVATE ${craft_compile_definitions} -DDEDICATED_SERVER)

target_link_libraries("${PROJECT_NAME}-client" PRIVATE ${craft_link_libraries})
target_link_libraries("${PROJECT_NAME}-server" PRIVATE ${craft_link_libraries})

target_compile_shaders("${PROJECT_NAME}-client"
    resources/assets/craft/shaders/cutout.frag
    resources/assets/craft/shaders/default.frag
    resources/assets/craft/shaders/default.vert
    resources/assets/craft/shaders/entity.frag
    resources/assets/craft/shaders/entity.vert
    resources/assets/craft/shaders/transparent.frag
)

#find_program(iwyu_path NAMES include-what-you-use iwyu REQUIRED)
#set_target_properties("${PROJECT_NAME}-client"
#    PROPERTIES
#        C_INCLUDE_WHAT_YOU_USE ${iwyu_path}
#        CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path}
#)
#set_target_properties("${PROJECT_NAME}-server"
#    PROPERTIES
#        C_INCLUDE_WHAT_YOU_USE ${iwyu_path}
#        CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path}
#)