#pragma once

#include "engine/tileMap/Tile.h"
#include "../../Parameters.h"

namespace WorldExtender {
	class PortalTile : public ChunkMapEngine::Tile {
	public:
		PortalTile(ChunkMapEngine::BaseGame* game, ChunkMapEngine::Texture texture, tile_type type, int version, glm::vec3 position = glm::vec3(0, 0, 0), float size = 1, int orientation = ChunkMapEngine::NULL_DIR);

		void reset() override;
		void interact() override;
	};
}