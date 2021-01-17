cmake_minimum_required(VERSION 3.15)
project(minecraft)

#include(FetchContent)

include(CMakeCxxModules/CXXModules.cmake)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_definitions(-DGLM_FORCE_XYZW_ONLY)

add_subdirectory(fmt)
add_subdirectory(stl)
add_subdirectory(json)
add_subdirectory(range-v3)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(PREBUILT_MODULE_PATH ${CMAKE_BINARY_DIR}/modules)

file(MAKE_DIRECTORY ${PREBUILT_MODULE_PATH})

function(add_module TARGET)
    set_source_files_properties(${ARGN} PROPERTIES LANGUAGE CXX)

    add_library(${TARGET} ${ARGN})
    target_link_libraries(${TARGET} stl)
    get_target_property(TARGET_COMPILE_OPTIONS ${TARGET} LINK_LIBRARIES)

    message("options: ${TARGET_COMPILE_OPTIONS}")

    add_custom_target(${TARGET}.pcm
            COMMAND
                ${CMAKE_CXX_COMPILER}
                "$<JOIN:$<TARGET_PROPERTY:${TARGET},COMPILE_OPTIONS>,\t>"
                -std=c++20
                -fmodules
#                -fimplicit-modules
#                -fbuiltin-module-map
#                -fimplicit-module-maps
                -c "${CMAKE_CURRENT_SOURCE_DIR}/${ARGN}"
                -Xclang -emit-module-interface
                -o "${PREBUILT_MODULE_PATH}/${TARGET}.pcm"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${ARGN}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    add_dependencies(${TARGET} ${TARGET}.pcm)
endfunction()

#add_compile_options(-fmodules)
#add_compile_options(-stdlib=libc++)
#add_compile_options(-fimplicit-modules)
#add_compile_options(-fimplicit-modules)
#add_compile_options(-fbuiltin-module-map)
#add_compile_options(-fimplicit-module-maps)
#add_compile_options(-fprebuilt-module-path=${PREBUILT_MODULE_PATH})

#add_library(raytrace src/raytrace.cpp)
#target_compile_options(raytrace PUBLIC " -Xclang -emit-module-interface -o ${PREBUILT_MODULE_PATH}/raytrace.pcm")
#target_link_libraries(raytrace stl)

#target_include_directories(raytrace.pcm
#    # The location of the headers before installation
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
#    # The location of the headers after installation
#    $<INSTALL_INTERFACE:include>
#)

#add_library(raytrace.pcm INTERFACE src/raytrace.cpp)
#target_sources(raytrace.pcm INTERFACE src/raytrace.cpp)
#target_compile_options(raytrace.pcm INTERFACE "-fmodules -Xclang -emit-module-interface -o ${PREBUILT_MODULE_PATH}/${name}.pcm")
#target_link_libraries(raytrace.pcm MODULE stl)

#add_compile_options(-fprofile-instr-generate)

#add_module(raytrace src/raytrace.hpp)
#target_link_libraries(raytrace stl)

add_executable(minecraft src/main.cpp src/graphics.hpp src/graphics.cpp src/input.hpp src/camera.hpp src/transform.hpp src/mesh.hpp src/free_camera_controls.hpp src/tile.hpp src/block_reader.hpp src/chunk_pos.hpp src/chunk.hpp src/texture_atlas.hpp src/resource_manager.hpp src/stb_image.hpp src/stb_image.cpp src/block_tessellator.cpp src/generator.cpp src/random.hpp src/tile.cpp src/raytrace.hpp src/worldgenregion.hpp)
target_link_libraries(minecraft atomic sfml-window sfml-system sfml-graphics GL GLEW stl fmt pthread lua nlohmann_json #[[raytrace]])

#add_dependencies(minecraft raytrace.pcm)

#target_link_module_libraries(minecraft raytrace)
#add_dependencies(minecraft ${PREBUILT_MODULE_PATH}/raytrace.pcm)
