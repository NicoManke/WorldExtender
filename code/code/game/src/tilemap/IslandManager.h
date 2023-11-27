#pragma once

#include "Island.h"

namespace WorldExtender {
	class Game;

	class IslandManager {
	public:
		IslandManager();
		~IslandManager() { };
		void setIslandPool();
		std::shared_ptr<ChunkMapEngine::Chunk> createIsland(ChunkMapEngine::BaseGame* game, int x = 0, int y = 0, int type = NULL_I);
		void createBridge(ChunkMapEngine::BaseGame* game, int direction, std::shared_ptr<ChunkMapEngine::Chunk> chunk);
	private:
		int islandCount = 0;
		bool hasPortal = false;

		int baseIslandWeight;
		int redIslandWeigth;
		int snowIslandWeigth;
		int stoneIslandWeigth;
		int manaIslandWeigth;
		int portalIslandWeigth;
		int totalWeigth;

		int plantIslandWeigth;

		void calculateTotalWeigth();
		int defineIslandType();
		void addStoneIslands();
		void addPlantIslands();
		void addFinalIslands();
	};
}