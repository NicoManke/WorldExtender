cmake_minimum_required(VERSION 3.20)

# set variables for source files
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h "../engine/src/rendering/Shader.cpp" "../engine/include/engine/rendering/Shader.h" "../engine/src/rendering/Mesh.cpp" "../engine/include/engine/rendering/Mesh.h" "../engine/src/entities/Entity.cpp" "../engine/include/engine/entities/Entity.h"   "../engine/include/engine/Assets.h"       "../engine/src/physics/ContactListener.cpp" "../engine/include/engine/physics/ContactListener.h")

# set executable name
set(EXE_FILE Game)

# add the executable target
add_executable(${EXE_FILE} ${SOURCE_FILES} "src/entities/Player.h" "src/entities/Player.cpp" "src/tilemap/IslandTileMap.h" "src/tilemap/IslandTileMap.cpp" "../engine/include/engine/tileMap/Tile.h" "../engine/src/tileMap/Tile.cpp" "../engine/include/engine/physics/Collider.h" "../engine/src/physics/Collider.cpp" "../engine/src/tileMap/Generator.cpp" "../engine/include/engine/Random.h"   "../engine/include/engine/rendering/TextureAtlas.h" "../engine/include/engine/rendering/Texture.h" "../engine/src/rendering/Texture.cpp" "../engine/src/rendering/TextureAtlas.cpp"   "../engine/include/engine/tileMap/Chunk.h" "../engine/src/tileMap/Chunk.cpp" "src/tilemap/Island.h" "src/tilemap/Island.cpp"    "../engine/include/engine/rendering/Animator.h" "../engine/src/rendering/Animator.cpp" "../engine/include/engine/Camera.h" "../engine/src/Camera.cpp" "../engine/src/tileMap/Area.cpp"   "src/interaction/InteractionManager.cpp" "../engine/src/ui/UI.cpp" "../engine/include/engine/ui/Canvas.h" "../engine/src/ui/Canvas.cpp" "src/inventory/Inventory.h" "src/inventory/Inventory.cpp" "src/tilemap/generators/IslandGenerator.h" "src/tilemap/generators/IslandGenerator.cpp" "src/tilemap/generators/StartIslandGenerator.h" "src/tilemap/generators/StartIslandGenerator.cpp" "src/tilemap/generators/IslandGeneratorFactory.h"  "src/tilemap/generators/PortalIslandGenerator.h" "src/tilemap/generators/PortalIslandGenerator.cpp" "src/tilemap/generators/StoneIslandGenerator.h" "src/tilemap/generators/StoneIslandGenerator.cpp" "src/tilemap/generators/ManaIslandGenerator.h" "src/tilemap/generators/ManaIslandGenerator.cpp" "src/interaction/ResourceCostManager.h" "src/interaction/ResourceCostManager.cpp" "src/tilemap/IslandManager.h" "src/tilemap/IslandManager.cpp" "src/tilemap/tiles/VoidTile.h" "src/tilemap/tiles/VoidTile.cpp" "src/tilemap/tiles/TileFactory.h"  "src/tilemap/tiles/PreBridgeTile.h" "src/tilemap/tiles/PreBridgeTile.cpp" "src/tilemap/tiles/ResourceTile.h" "src/tilemap/tiles/ResourceTile.cpp" "src/tilemap/tiles/PortalTile.h" "src/tileMap/tiles/PortalTile.cpp" "src/tilemap/generators/PlantIslandGenerator.h" "src/tilemap/generators/PlantIslandGenerator.cpp")

# require C++ 17 compiler
target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

#link with engine
target_link_libraries(${EXE_FILE} PRIVATE Engine)

target_compile_definitions(${EXE_FILE} PRIVATE DEBUG_ASSET_ROOT=./assets/)