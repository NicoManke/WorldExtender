#include "InteractionManager.h"
#include "../Game.h"
#include "engine/Assets.h"
#include <iostream>

namespace WorldExtender {
	InteractionManager::InteractionManager(Game* game, ResourceCostManager* rcManager, IslandTileMap* tileMap, Player* player, std::shared_ptr<ChunkMapEngine::UI> tileMarker) : rcManager(rcManager), tileMap(tileMap), player(player), game(game), tileMarker(tileMarker) {
		init();
	}

	InteractionManager::InteractionManager() {
		init();
	}

	InteractionManager::~InteractionManager() {
		interactionDenied.reset();
		interactionStone.reset();
		interactionMana.reset();
		interactionWood.reset();
		interactionPortal.reset();
		creationIsland.reset();
		creationBridge.reset();
	};

	InteractionManager& InteractionManager::operator=(const InteractionManager& other)
	{
		if (this != &other) {
			game = other.game;
			rcManager = other.rcManager;
			tileMap = other.tileMap;
			player = other.player;
			tileMarker = std::move(other.tileMarker);
			interactionDenied = std::move(other.interactionDenied);
			interactionStone = std::move(other.interactionStone);
			interactionMana = std::move(other.interactionMana);
			interactionWood = std::move(other.interactionWood);
			interactionPortal = std::move(other.interactionPortal);
			creationIsland = std::move(other.creationIsland);
			creationBridge = std::move(other.creationBridge);
		}
		return *this;
	}

	void InteractionManager::init() {
		interactionDenied = std::make_shared<SoLoud::Wav>();
		interactionDenied->load(ChunkMapEngine::resolveAssetPath("audio/denied_feedback.mp3").string().c_str());
		interactionDenied->setSingleInstance(true);
		interactionStone = std::make_shared < SoLoud::Wav>();
		interactionStone->load(ChunkMapEngine::resolveAssetPath("audio/stone_interact.mp3").string().c_str());
		interactionStone->setSingleInstance(true);
		interactionMana = std::make_shared < SoLoud::Wav>();
		interactionMana->load(ChunkMapEngine::resolveAssetPath("audio/plant_interact.mp3").string().c_str());
		interactionMana->setSingleInstance(true);
		interactionWood = std::make_shared < SoLoud::Wav>();
		interactionWood->load(ChunkMapEngine::resolveAssetPath("audio/wood_interact.mp3").string().c_str());
		interactionWood->setSingleInstance(true);
		interactionPortal = std::make_shared < SoLoud::Wav>();
		interactionPortal->load(ChunkMapEngine::resolveAssetPath("audio/portal_interact.mp3").string().c_str());
		interactionPortal->setSingleInstance(true);
		creationIsland = std::make_shared < SoLoud::Wav>();
		creationIsland->load(ChunkMapEngine::resolveAssetPath("audio/island_creation.mp3").string().c_str());
		creationIsland->setSingleInstance(true);
		creationBridge = std::make_shared < SoLoud::Wav>();
		creationBridge->load(ChunkMapEngine::resolveAssetPath("audio/bridge_creation.mp3").string().c_str());
		creationBridge->setSingleInstance(true);
	}

	void InteractionManager::manageInteractions(Game* game) {
		this->game = game;
		manageKeyInputs(game->getWindow());

		auto tile = tileMap->getInteractableTile(player->getTurnDirection() / 2);
		if (tile != nullptr) {
			if (tile->isInteractable()) {
				if (player->IsInteracting() == false) {
					auto pos = tile->getPosition();
					tileMarker->setPosition({ pos.x, pos.y, 0.0 });

					auto type = tile->getType();

					if (type == PRE_BRIDGE) {
						if (tileMap->isChunkInDirection(tile->getOrientation())) {
							rcManager->displayBridgeAction();
						}
						else {
							rcManager->displayIslandAction();
						}
					}
					else if (type == PORTAL) {
						rcManager->displayPortalAction();
					}
					else if (type == STONE) {
						rcManager->displayStoneAction();
					}
					else if (type == MANA) {
						rcManager->displayManaAction();
					}
					else if (type == BUSH) {
						rcManager->displayWoodAction();
					}
				}
			}
			else {
				tileMarker->setPosition({ 0, 0, 100 });
				rcManager->resetInfoIcons();
			}
		}
		else {
			rcManager->resetInfoIcons();
		}
	}

	void InteractionManager::onKeyDownSPACE() {
		if (player->IsInteracting() == false) {
			auto playerDir = player->getTurnDirection();
			auto tile = tileMap->getInteractableTile(playerDir / 2);

			if (tile != nullptr && tile->isInteractable()) {
				auto tileOrient = tile->getOrientation();
				auto canInteract = true;
				auto inv = player->getIventory();
				if (tile->getType() == PRE_BRIDGE) {
					if (tileMap->isChunkInDirection(tileOrient) && inv->getWoodCount() >= 5) {
						inv->decreaseWoodCount(5);
						tileMap->connectChunks(game, tileOrient);
						game->getAudioSystem()->play(*creationBridge, 10);
					}
					else if (tileMap->isChunkInDirection(tileOrient) == false && inv->getStoneCount() >= 5 && inv->getManaCount() >= 5 && inv->getWoodCount() >= 5) {
						inv->decreaseStoneCount(5);
						inv->decreaseManaCount(5);
						inv->decreaseWoodCount(5);
						tileMap->expandMap(game, tileOrient);
						game->getAudioSystem()->play(*creationIsland, 10);
					}
					else {
						canInteract = false;
					}
				}
				else if (tile->getType() == PORTAL) {
					if (inv->getManaCount() >= 50) {
						inv->decreaseManaCount(50);
						game->getAudioSystem()->play(*interactionPortal, 20);
						game->endGame();
					}
					else {
						canInteract = false;
					}
				}

				if (canInteract) {
					player->startInteractionAnimation();
					player->interact(tile->isInteractable(), tile->getType());
					auto type = tile->getType();
					switch (type) {
					case STONE:
						game->getAudioSystem()->play(*interactionStone);
						break;
					case MANA:
						game->getAudioSystem()->play(*interactionMana);
						break;
					case BUSH:
						game->getAudioSystem()->play(*interactionWood);
						break;
					}
					tile->interact();
				}
				else {
					game->getAudioSystem()->play(*interactionDenied, 5);
				}
			}
		}
	}

	void InteractionManager::onKeyDownSHIFT() { }

	void InteractionManager::onKeyDownESC() {
		glfwSetWindowShouldClose(window, true);
	}

	void InteractionManager::onKeyDownTAB() { }
	void InteractionManager::onKeyDownW() { }
	void InteractionManager::onKeyDownA() { }
	void InteractionManager::onKeyDownS() { }
	void InteractionManager::onKeyDownD() { }
	void InteractionManager::onKeyDownQ() { }
	void InteractionManager::onKeyDownE() { }
	void InteractionManager::onKeyDownR() { }
	void InteractionManager::onKeyDownF() { }
}