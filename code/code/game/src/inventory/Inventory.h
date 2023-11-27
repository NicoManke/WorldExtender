#pragma once

#include <memory>
#include "engine/ui/Canvas.h"

using namespace std;

constexpr int DIGIT_ROW = 0;
constexpr int STONE_ITEM = 0;
constexpr int MANA_ITEM = 1;
constexpr int WOOD_ITEM = 2;

namespace WorldExtender {
	class Inventory {
	public:
		Inventory();
		~Inventory();
		void increaseStoneCount();
		void increaseManaCount();
		void increaseWoodCount();
		void decreaseStoneCount(int deficit);
		void decreaseManaCount(int deficit);
		void decreaseWoodCount(int deficit);
		int getStoneCount() { return stoneCount; }
		int getManaCount() { return manaCount; }
		int getWoodCount() { return woodCount; }
		ChunkMapEngine::Canvas* getCanvas() { return &canvas; }
		void draw(ChunkMapEngine::BaseGame* game);

	private:
		ChunkMapEngine::Canvas canvas;
		
		int stoneCount = 0;
		shared_ptr<ChunkMapEngine::UI> stoneIcon;
		shared_ptr<ChunkMapEngine::UI> stoneTensIcon;
		shared_ptr<ChunkMapEngine::UI> stoneOnesIcon;
		void updateStoneCounter(int count);

		int manaCount = 0;
		shared_ptr<ChunkMapEngine::UI> manaIcon;
		shared_ptr<ChunkMapEngine::UI> manaTensIcon;
		shared_ptr<ChunkMapEngine::UI> manaOnesIcon;
		void updateManaCounter(int count);

		int woodCount = 0;
		shared_ptr<ChunkMapEngine::UI> woodIcon;
		shared_ptr<ChunkMapEngine::UI> woodTensIcon;
		shared_ptr<ChunkMapEngine::UI> woodOnesIcon;
		void updateWoodCounter(int count);
	};
}