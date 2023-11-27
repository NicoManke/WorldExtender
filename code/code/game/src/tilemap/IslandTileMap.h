#pragma once

#include "engine/tileMap/TileMap.h"
#include "IslandManager.h"

namespace WorldExtender {
	class Game;

	class IslandTileMap : public ChunkMapEngine::TileMap
	{
	public:
		~IslandTileMap();
		IslandTileMap();

		void initializeStartingRegion(ChunkMapEngine::BaseGame* game, ChunkMapEngine::Entity* player, int type = START_I) override;
		void expandMap(ChunkMapEngine::BaseGame* game, int direction) override;
		void connectChunks(ChunkMapEngine::BaseGame* game, int direction) override;

	private:
		IslandManager islandManager;
	};
}