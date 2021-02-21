cmake_minimum_required(VERSION 3.15)
project(minecraft)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS OFF)

include_directories(.)
include_directories(imgui)

add_definitions(-DGLM_FORCE_XYZW_ONLY)

add_subdirectory(fmt)
add_subdirectory(stl)
add_subdirectory(json)
add_subdirectory(glm)
add_subdirectory(asyncplusplus)

add_library(imgui STATIC imgui/imconfig.h imgui/imgui.cpp imgui/imgui.h imgui/imgui_draw.cpp imgui/imgui_internal.h imgui/imgui_tables.cpp imgui/imgui_widgets.cpp)
add_library(imgui-sdl STATIC imgui/backends/imgui_impl_sdl.cpp imgui/backends/imgui_impl_sdl.h imgui/backends/imgui_impl_opengl3.h imgui/backends/imgui_impl_opengl3.cpp)

target_link_libraries(imgui-sdl imgui SDL2)

add_executable(minecraft src/main.cpp src/graphics.hpp src/graphics.cpp src/input.hpp src/camera.hpp src/transform.hpp src/mesh.hpp src/Block.hpp src/BlockReader.hpp src/util/math/ChunkPos.hpp src/world/chunk/Chunk.hpp src/TextureAtlas.hpp src/resource_manager.hpp src/stb_image.hpp src/stb_image.cpp src/BlockTessellator.cpp src/util/Random.hpp src/Block.cpp src/raytrace.hpp src/worldgenregion.hpp src/BlockTable.hpp src/world/gen/layer/AddBambooForestLayer.hpp src/world/gen/layer/AddIslandLayer.hpp src/world/gen/layer/AddMushroomIslandLayer.hpp src/world/gen/layer/AddSnowLayer.hpp src/world/gen/layer/BiomeLayer.hpp src/world/gen/layer/DeepOceanLayer.hpp src/world/gen/layer/EdgeBiomeLayer.hpp src/world/gen/layer/EdgeLayer.hpp src/world/gen/layer/HillsLayer.hpp src/world/gen/layer/IslandLayer.hpp src/world/gen/layer/MixOceansLayer.hpp src/world/gen/layer/MixRiverLayer.hpp src/world/gen/layer/OceanLayer.hpp src/world/gen/layer/RareBiomeLayer.hpp src/world/gen/layer/RemoveTooMuchOceanLayer.hpp src/world/gen/layer/RiverLayer.hpp src/world/gen/layer/ShoreLayer.hpp src/world/gen/layer/SmoothLayer.hpp src/world/gen/layer/StartRiverLayer.hpp src/world/gen/layer/ZoomLayer.hpp src/world/gen/INoiseRandom.hpp src/world/gen/ImprovedNoiseGenerator.hpp src/world/gen/SimplexNoiseGenerator.hpp src/world/gen/layer/traits/IDimTransformer.hpp src/world/gen/layer/traits/IAreaTransformer1.hpp src/world/gen/layer/traits/IAreaTransformer2.hpp src/world/gen/layer/traits/IDimOffset0Transformer.hpp src/world/gen/layer/traits/IDimOffset1Transformer.hpp src/world/gen/layer/traits/IC1Transformer.hpp src/world/gen/layer/traits/IBishopTransformer.hpp src/world/gen/area/IArea.hpp src/world/gen/layer/LayerUtil.hpp src/world/gen/layer/traits/IC0Transformer.hpp src/world/gen/layer/traits/ICastleTransformer.hpp src/world/gen/layer/traits/IAreaTransformer0.hpp src/world/gen/IExtendedNoiseRandom.hpp src/world/gen/area/IAreaFactory.hpp src/world/gen/LazyAreaLayerContext.hpp src/util/FastRandom.hpp src/world/gen/layer/LayerUtil.cpp src/world/gen/layer/Layer.hpp src/world/biome/Biome.hpp src/world/gen/NoiseChunkGenerator.cpp src/world/gen/NoiseChunkGenerator.hpp src/world/gen/INoiseGenerator.hpp src/world/gen/PerlinNoiseGenerator.cpp src/world/gen/PerlinNoiseGenerator.hpp src/world/gen/OctavesNoiseGenerator.cpp src/world/gen/OctavesNoiseGenerator.hpp src/world/gen/ChunkGenerator.hpp src/world/gen/ChunkGenerator.cpp src/SurfaceBuilder.h src/DefaultSurfaceBuilder.cpp src/DefaultSurfaceBuilder.h src/world/biome/Biome.cpp src/BlockData.h src/ChunkRenderCache.h src/world/gen/blockplacer/BlockPlacer.hpp src/world/gen/blockplacer/ColumnBlockPlacer.hpp src/ids.cpp src/ids.h)
target_link_libraries(minecraft atomic GL GLEW stl fmt pthread nlohmann_json glm imgui-sdl Async++)