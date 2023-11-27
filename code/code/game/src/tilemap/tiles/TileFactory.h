#pragma once

#include "../../Parameters.h"
#include "VoidTile.h"
#include "PortalTile.h"
#include "PreBridgeTile.h"
#include "ResourceTile.h"
#include <memory>

namespace WorldExtender {
    class TileFactory {
    public:
        static std::shared_ptr<ChunkMapEngine::Tile> createTile(ChunkMapEngine::BaseGame* game, ChunkMapEngine::Texture texture, tile_type type, int version, glm::vec3 position, float size, int orientation = ChunkMapEngine::NULL_DIR) {
            if (type == VOIDS) {
                return std::make_shared<VoidTile>(game, texture, type, version, position, size);
            }
            else if (type == PRE_BRIDGE) {
                return std::make_shared<PreBridgeTile>(game, texture, type, version, position, size, orientation);
            }
            else if (type == STONE || type == MANA || type == BUSH) {
                return std::make_shared<ResourceTile>(game, texture, type, version, position, size);
            }
            else if (type == PORTAL) {
                return std::make_shared<PortalTile>(game, texture, type, version, position, size);
            }
            else {
                return std::make_shared <ChunkMapEngine::Tile>(game, texture, type, version, position, size);
            }
        }
    };
}