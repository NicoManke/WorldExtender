#pragma once

#include "engine/InputManager.h"
#include "ResourceCostManager.h"
#include "../entities/Player.h"
#include "../tilemap/IslandTileMap.h"
#include "engine/ui/UI.h"
#include <soloud_wav.h>
#include <memory>

namespace WorldExtender {
	class Game;

	class InteractionManager : public ChunkMapEngine::InputManager {
	public:
		InteractionManager(Game* game, ResourceCostManager* rcManager, IslandTileMap* tileMap, Player* player, std::shared_ptr<ChunkMapEngine::UI> tileMarker);
		InteractionManager(); 
		InteractionManager& operator=(const InteractionManager& other);
		~InteractionManager();
		void init();
		void manageInteractions(Game* game);

	protected:
		void onKeyDownSPACE() override;
		void onKeyDownSHIFT() override;
		void onKeyDownESC() override;
		void onKeyDownTAB() override;
		void onKeyDownW() override;
		void onKeyDownA() override;
		void onKeyDownS() override;
		void onKeyDownD() override;
		void onKeyDownQ() override;
		void onKeyDownE() override;
		void onKeyDownR() override;
		void onKeyDownF() override;
	private:
		ResourceCostManager* rcManager;
		IslandTileMap* tileMap;
		Player* player;
		Game* game;
		std::shared_ptr<ChunkMapEngine::UI> tileMarker = nullptr;

		std::shared_ptr<SoLoud::Wav> interactionDenied;
		std::shared_ptr<SoLoud::Wav> interactionStone;
		std::shared_ptr<SoLoud::Wav> interactionMana;
		std::shared_ptr<SoLoud::Wav> interactionWood;
		std::shared_ptr<SoLoud::Wav> interactionPortal;
		std::shared_ptr<SoLoud::Wav> creationIsland;
		std::shared_ptr<SoLoud::Wav> creationBridge;
	};
}