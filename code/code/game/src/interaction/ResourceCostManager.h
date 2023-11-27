#pragma once

#include "engine/ui/Canvas.h"
#include "../Parameters.h"

using namespace std;

namespace WorldExtender {
	class Game;

	struct Costs {
		int stoneCost;
		int manaCost;
		int woodCost;
	};

	class ResourceCostManager {
	public:
		ResourceCostManager();
		ChunkMapEngine::Canvas* getCanvas() { return &canvas; }
		void draw(ChunkMapEngine::BaseGame* game);
		void updateIslandCosts(Costs newCosts);
		void updateBridgeCosts(Costs newCosts);
		void updatePortalCosts(Costs newCosts);
		void resetInfoIcons();
		void displayStoneAction();
		void displayManaAction();
		void displayWoodAction();
		void displayIslandAction();
		void displayBridgeAction();
		void displayPortalAction();
	private:
		void displayCosts(Costs costs);

		Costs islandCosts = { 5, 5, 5 };
		Costs bridgeCosts = { 0, 0, 5 };
		Costs portalCosts = { 0, 50, 0 };
		Costs stoneGain = { -1, 0, 0 };
		Costs manaGain = { 0, -1, 0 };
		Costs woodGain = { 0, 0, -1 };
	
		ChunkMapEngine::Canvas canvas;

		shared_ptr<ChunkMapEngine::UI> actionIcon;

		shared_ptr<ChunkMapEngine::UI> stoneIcon;
		shared_ptr<ChunkMapEngine::UI> stoneTensIcon;
		shared_ptr<ChunkMapEngine::UI> stoneOnesIcon;
		shared_ptr<ChunkMapEngine::UI> stoneOperandIcon;
		void updateStoneCounter(int count, bool add);

		shared_ptr<ChunkMapEngine::UI> manaIcon;
		shared_ptr<ChunkMapEngine::UI> manaTensIcon;
		shared_ptr<ChunkMapEngine::UI> manaOnesIcon;
		shared_ptr<ChunkMapEngine::UI> manaOperandIcon;
		void updateManaCounter(int count, bool add);

		shared_ptr<ChunkMapEngine::UI> woodIcon;
		shared_ptr<ChunkMapEngine::UI> woodTensIcon;
		shared_ptr<ChunkMapEngine::UI> woodOnesIcon;
		shared_ptr<ChunkMapEngine::UI> woodOperandIcon;
		void updateWoodCounter(int count, bool add);
	};
}
