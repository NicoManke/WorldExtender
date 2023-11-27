#include "engine/tileMap/Chunk.h"
#include "engine/Settings.h"
#include <iostream>

namespace ChunkMapEngine {
	Chunk::Chunk(int x, int y, int rowsCount, int columnsCount) : Area(
		(x - 0.5) * ChunkMapEngine::SCALING * columnsCount,
		(y + 0.5) * ChunkMapEngine::SCALING * rowsCount,
		(x + 0.5) * ChunkMapEngine::SCALING * columnsCount,
		(y - 0.5) * ChunkMapEngine::SCALING * rowsCount)
	{
		tiles = std::vector<std::shared_ptr<Tile>>(); 
		switchColliderTiles = std::vector<std::shared_ptr<Tile>>();
		center = glm::vec2(x, y);
	}

	Chunk::~Chunk() {

	}

	void Chunk::draw(BaseGame* game) {
		for (auto& tile : tiles) {
			tile->draw(game);
		}
	}

	void Chunk::cullColliders(bool culled) {
		if (switchColliderTiles.empty()) { 
			return; 
		}
		for (std::shared_ptr<Tile> colliderTile : switchColliderTiles) {
			colliderTile->activateCollider(!culled);
		}
	}
}