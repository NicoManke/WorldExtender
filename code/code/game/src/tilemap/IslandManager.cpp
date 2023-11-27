#include "IslandManager.h"
#include "tiles/TileFactory.h"
#include "../Game.h"
#include "engine/Random.h"

namespace WorldExtender {
	IslandManager::IslandManager() {
		baseIslandWeight = 8;
		redIslandWeigth = 3;
		snowIslandWeigth = 3;
		stoneIslandWeigth = 0;
		manaIslandWeigth = 0;
		portalIslandWeigth = 0;

		plantIslandWeigth = 0;

		calculateTotalWeigth();
	}

	void IslandManager::setIslandPool() {
		if (islandCount == PLANT_STAGE) {
			addPlantIslands();
		}
		else if (islandCount == STONE_STAGE) {
			addStoneIslands();
		}
		else if (islandCount == FINAL_STAGE) {
			addFinalIslands();
		}
		else if (islandCount > FINAL_STAGE && hasPortal == false) {
			portalIslandWeigth =+ 3;
			calculateTotalWeigth();
		}
	}

	void IslandManager::addStoneIslands() {
		stoneIslandWeigth = 3;
		calculateTotalWeigth();
	}

	void IslandManager::addPlantIslands() {
		plantIslandWeigth = 3;
		calculateTotalWeigth();
	}

	void IslandManager::addFinalIslands() {
		manaIslandWeigth = 3;
		portalIslandWeigth = 1;
		calculateTotalWeigth();
	}

	void IslandManager::calculateTotalWeigth() {
		totalWeigth = baseIslandWeight + redIslandWeigth + snowIslandWeigth + stoneIslandWeigth + manaIslandWeigth + portalIslandWeigth + plantIslandWeigth;
	}

	int IslandManager::defineIslandType() {
		auto random = ChunkMapEngine::Random::floatRange(0.0f, 1.0f);
		auto randomType = BASE_I;
		auto p_step_base = (double)baseIslandWeight / totalWeigth;
		auto p_step_red = (double)(baseIslandWeight + redIslandWeigth) / totalWeigth;
		auto p_step_snow = (double)(baseIslandWeight + redIslandWeigth + snowIslandWeigth) / totalWeigth;
		auto p_step_plant = (double)(baseIslandWeight + redIslandWeigth + snowIslandWeigth + plantIslandWeigth) / totalWeigth;
		auto p_step_stone = (double)(baseIslandWeight + redIslandWeigth + snowIslandWeigth + plantIslandWeigth + stoneIslandWeigth) / totalWeigth;
		auto p_step_final = (double)(baseIslandWeight + redIslandWeigth + snowIslandWeigth + plantIslandWeigth + stoneIslandWeigth + manaIslandWeigth) / totalWeigth;
		if (random > p_step_base && random <= p_step_red) {
			randomType = RED_I;
		}
		else if (random > (p_step_red) && random <= p_step_snow) {
			randomType = SNOW_I;
		}
		// stage 2
		else if (random > p_step_snow && random <= p_step_plant) {
			randomType = PLANT_I;
		}
		// stage 3
		else if (random > p_step_plant && random <= p_step_stone) {
			randomType = STONE_I;
		}
		// stage 4
		else if (random > p_step_stone && random <= p_step_final) {
			randomType = MANA_I;
		}
		else if (random > p_step_final) {
			randomType = PORTAL_I;
		}
		return randomType;
	}

	std::shared_ptr<ChunkMapEngine::Chunk> IslandManager::createIsland(ChunkMapEngine::BaseGame* game, int x, int y, int type) {
		islandCount++;
		setIslandPool();
		if (type == NULL_I) {
			type = defineIslandType();
		}
		if (type == PORTAL_I) {
			hasPortal = true;
			portalIslandWeigth = 0;
			calculateTotalWeigth();
		}
		return std::make_shared<Island>(game, type, x, y);;
	}

	void IslandManager::createBridge(ChunkMapEngine::BaseGame* game, int direction, std::shared_ptr<ChunkMapEngine::Chunk> chunk) {

		if (direction <= 8 && direction >= 0) {
			//inverse direction
			int toDirection = (direction + 4) % 8;
			// bridge
			int pos = 0;
			int prePos = 0;
			int bridgeVersion = 0;
			int preVersion = 0;
			switch (toDirection) {
			case ChunkMapEngine::NORTH:
				pos = (WIDTH / 2) + WIDTH * (HEIGHT - 1);
				prePos = pos - WIDTH;
				bridgeVersion = 2;
				preVersion = 3;
				break;
			case ChunkMapEngine::EAST:
				pos = (HEIGHT / 2) * WIDTH;
				prePos = pos + 1;
				bridgeVersion = 0;
				preVersion = 1;
				break;
			case ChunkMapEngine::SOUTH:
				pos = WIDTH / 2;
				prePos = pos + WIDTH;
				bridgeVersion = 1;
				preVersion = 0;
				break;
			case ChunkMapEngine::WEST:
				pos = ((HEIGHT / 2) * WIDTH) + WIDTH - 1;
				prePos = pos - 1;
				bridgeVersion = 0;
				preVersion = 2;
				break;
			default:
				break;
			}

			auto bridgeTile = chunk->getTiles()->at(pos);
			auto preBridgeTile = chunk->getTiles()->at(prePos);
			bridgeTile->removeCollider(game->getPhysicsWorld());
			auto weg = dynamic_cast<Game*>(game);
			chunk->getTiles()->at(pos) = TileFactory::createTile(game, weg->getTextureAtlas()->getTexture(), BRIDGE, bridgeVersion, bridgeTile->getPosition(), ChunkMapEngine::SCALING);
			preBridgeTile->changeVersion(preVersion);
			preBridgeTile->interact();
			if (bridgeVersion == 0) {
				chunk->getTiles()->at(pos + WIDTH)->changeVersion(4);
			}
		}
	}
}