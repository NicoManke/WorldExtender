#include "Island.h"
#include "generators/IslandGeneratorFactory.h"
#include "tiles/TileFactory.h"
#include <iostream>
#include "../Game.h"
#include <typeinfo>

namespace WorldExtender {
	Island::Island(ChunkMapEngine::BaseGame* game, int type, int x, int y) : ChunkMapEngine::Chunk(x, y, HEIGHT, WIDTH) {
		this->type = type;

		layout = std::vector<int>();
		versions = std::vector<int>();
		generator = IslandGeneratorFactory::createGenerator(type);

		generate();
		variate();
		populate(type, game);
	};

	void Island::generate() {
		layout = generator->generateChunk();
	}

	void Island::variate() {
		versions = generator->defineTileVersions(layout);
	}

	bool isNextToBridge(int location) {
		switch (location) {
		case (WIDTH / 2) - 1:
			return true;
			break;
		case (WIDTH / 2) + 1:
			return true;
			break;
		case (((HEIGHT / 2) * WIDTH) + WIDTH - 1) - WIDTH:
			return true;
			break;
		case (((HEIGHT / 2) * WIDTH) + WIDTH - 1) + WIDTH:
			return true;
			break;
		case ((WIDTH / 2) + WIDTH * (HEIGHT - 1)) - 1:
			return true;
			break;
		case ((WIDTH / 2) + WIDTH * (HEIGHT - 1)) + 1:
			return true;
			break;
		case ((HEIGHT / 2) * WIDTH) - WIDTH:
			return true;
			break;
		case ((HEIGHT / 2) * WIDTH) + WIDTH:
			return true;
			break;
		default:
			return false;
		}
	}

	int getPreBridgeOrientation(int location) {
		switch (location) {
		case (int)(WIDTH * 1.5):
			return ChunkMapEngine::NORTH;
			break;
		case (int)(WIDTH * ((HEIGHT + 1) * 0.5) - 2):
			return ChunkMapEngine::EAST;
			break;
		case (int)(WIDTH * (HEIGHT - 1) - (0.5 * WIDTH)):
			return ChunkMapEngine::SOUTH;
			break;
		case (int)(WIDTH * ((HEIGHT - 1) * 0.5) + 1):
			return ChunkMapEngine::WEST;
			break;
		default:
			return ChunkMapEngine::NULL_DIR;
		}
	}

	void Island::populate(int type, ChunkMapEngine::BaseGame* game) {
		for (int row = 0; row < HEIGHT; row++) {
			for (int column = 0; column < WIDTH; column++) {
				auto location = row * WIDTH + column;
				auto tileType = layout[location];
				auto version = versions[location];
				auto orientation = ChunkMapEngine::NULL_DIR;

				auto x = (column + (-0.5 + ISLAND_OFFSET * center.x) * WIDTH + ChunkMapEngine::CENTERING) * ChunkMapEngine::SCALING;
				auto y = (-row   + ( 0.5 + ISLAND_OFFSET * center.y) * HEIGHT - ChunkMapEngine::CENTERING) * ChunkMapEngine::SCALING;

				if (tileType == PRE_BRIDGE) {
					orientation = getPreBridgeOrientation(location);
				}

				auto weg = dynamic_cast<Game*>(game);

				std::shared_ptr<ChunkMapEngine::Tile> tile;
				if (type == BASE_I || type == START_I) {
					tile = TileFactory::createTile(game, weg->getTextureAtlas()->getTexture(), tileType, version, glm::vec3{ x, y, 0 }, ChunkMapEngine::SCALING, orientation);
				}
				else if (type == RED_I) {
					tile = TileFactory::createTile(game, weg->getTextureAtlasRed()->getTexture(), tileType, version, glm::vec3{ x, y, 0 }, ChunkMapEngine::SCALING, orientation);
				}
				else if (type == SNOW_I) {
					tile = TileFactory::createTile(game, weg->getTextureAtlasSnow()->getTexture(), tileType, version, glm::vec3{ x, y, 0 }, ChunkMapEngine::SCALING, orientation);
				}
				else if (type == STONE_I) {
					tile = TileFactory::createTile(game, weg->getTextureAtlasStone()->getTexture(), tileType, version, glm::vec3{ x, y, 0 }, ChunkMapEngine::SCALING, orientation);
				}
				else if (type == MANA_I) {
					tile = TileFactory::createTile(game, weg->getTextureAtlasMana()->getTexture(), tileType, version, glm::vec3{ x, y, 0 }, ChunkMapEngine::SCALING, orientation);
				}
				else if (type == PORTAL_I) {
					tile = TileFactory::createTile(game, weg->getTextureAtlasPortal()->getTexture(), tileType, version, glm::vec3{ x, y, 0 }, ChunkMapEngine::SCALING, orientation);
				}
				else {
					tile = TileFactory::createTile(game, weg->getTextureAtlas()->getTexture(), tileType, version, glm::vec3{ x, y, 0 }, ChunkMapEngine::SCALING, orientation);
				}

				if (tileType == VOIDS && isNextToBridge(location)) {
					switchColliderTiles.push_back(tile);
				}
				cullColliders(true);
				tiles.push_back(std::move(tile));
			}
		}
	}
}