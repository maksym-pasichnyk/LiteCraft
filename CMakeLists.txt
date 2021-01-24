cmake_minimum_required(VERSION 3.15)
project(minecraft)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_definitions(-DGLM_FORCE_XYZW_ONLY)

add_subdirectory(fmt)
add_subdirectory(stl)
add_subdirectory(json)
add_subdirectory(range-v3)
add_subdirectory(glm)

set(CMAKE_CXX_STANDARD 20)

add_executable(minecraft src/main.cpp src/graphics.hpp src/graphics.cpp src/input.hpp src/camera.hpp src/transform.hpp src/mesh.hpp src/tile.hpp src/block_reader.hpp src/chunk_pos.hpp src/chunk.hpp src/texture_atlas.hpp src/resource_manager.hpp src/stb_image.hpp src/stb_image.cpp src/block_tessellator.cpp src/generator.cpp src/random.hpp src/tile.cpp src/raytrace.hpp src/worldgenregion.hpp)
target_link_libraries(minecraft atomic sfml-window sfml-system sfml-graphics GL GLEW stl fmt pthread nlohmann_json glm)

#add_dependencies(minecraft raytrace.pcm)

#target_link_module_libraries(minecraft raytrace)
#add_dependencies(minecraft ${PREBUILT_MODULE_PATH}/raytrace.pcm)
