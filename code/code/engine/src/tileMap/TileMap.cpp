#include "engine/tileMap/TileMap.h"
#include "engine/BaseGame.h"
#include "engine/Settings.h"
#include <iostream>

namespace ChunkMapEngine {

	TileMap::TileMap(int chunkWidth, int chunkHeight) {
		this->chunkWidth = chunkWidth;
		this->chunkHeight = chunkHeight;
		chunks = std::vector<std::shared_ptr<Chunk>>();
	};

	void TileMap::updateChunks() {
		auto playerPos = player->getPosition();
		if (currentChunk->containsPoint(playerPos.x, playerPos.y)) {
			return;
		}

		for (auto chunk : visibleChunks) {
			if (chunk) {
				if (chunk->containsPoint(playerPos.x, playerPos.y)) {
					// set the void colliders of the Chunk we are leaving inactive
					currentChunk->cullColliders(true);
					currentChunk = chunk;
					// set the void colliders of the Chunk we are entering active
					currentChunk->cullColliders(false);

					// update visible chunks
					visibleChunks.clear();
					// adding the chunks clock wise
					visibleChunks.push_back(chunk->neighbours[0]);
					visibleChunks.push_back(chunk->neighbours[1]);
					visibleChunks.push_back(chunk->neighbours[2]);
					visibleChunks.push_back(chunk->neighbours[3]);
					visibleChunks.push_back(chunk->neighbours[4]);
					visibleChunks.push_back(chunk->neighbours[5]);
					visibleChunks.push_back(chunk->neighbours[6]);
					visibleChunks.push_back(chunk->neighbours[7]);

					// interactable tiles
					auto tiles = currentChunk->getTiles();
					for (int i = 0; i < tiles->size(); i++) {
						if (tiles->at(i)->containsPoint(playerPos.x, playerPos.y)) {
							setTiles(i);
							break;
						}
					}
					break;
				}
			}
			continue;
		}
	}

	void TileMap::updateTiles() {
		auto playerPos = player->getPosition();
		if (currentTile->containsPoint(playerPos.x, playerPos.y)) {
			return;
		}

		for (int i = 0; i < neighbourTiles.size(); i++) {
			auto tile = neighbourTiles.at(i);
			if (tile) {
				if (tile->containsPoint(playerPos.x, playerPos.y)) {
					currentTile = tile;
					switch (i) {
					case ChunkMapEngine::NORTH:
						setTiles(currentTileLocation - chunkWidth);
						break;
					case ChunkMapEngine::NORTH_EAST:
						setTiles(currentTileLocation - chunkWidth + 1);
						break;
					case ChunkMapEngine::EAST:
						setTiles(currentTileLocation + 1);
						break;
					case ChunkMapEngine::SOUTH_EAST:
						setTiles(currentTileLocation + chunkWidth + 1);
						break;
					case ChunkMapEngine::SOUTH:
						setTiles(currentTileLocation + chunkWidth);
						break;
					case ChunkMapEngine::SOUTH_WEST:
						setTiles(currentTileLocation + chunkWidth - 1);
						break;
					case ChunkMapEngine::WEST:
						setTiles(currentTileLocation - 1);
						break;
					case ChunkMapEngine::NORTH_WEST:
						setTiles(currentTileLocation - chunkWidth - 1);
						break;
					default:
						setTiles(i);
					}
				}
			}
		}
	}

	void TileMap::setTiles(int location) {
		auto tiles = currentChunk->getTiles();
		currentTileLocation = location;
		currentTile = tiles->at(location);
		// north
		neighbourTiles[0] = (location - chunkWidth) >= 0 ? tiles->at(location - chunkWidth) : nullptr;
		interactableTiles[0] = neighbourTiles[0];
		// north-east
		auto ne_loc = location - chunkWidth + 1;
		neighbourTiles[1] = (ne_loc) % chunkWidth > (location - chunkWidth) % chunkWidth && ne_loc >= 0 ? tiles->at(ne_loc) : nullptr;
		// east
		neighbourTiles[2] = ((location + 1) % chunkWidth) > (location % chunkWidth) ? tiles->at(location + 1) : nullptr;
		interactableTiles[1] = neighbourTiles[2];
		// south-east
		auto se_loc = location + chunkWidth + 1;
		neighbourTiles[3] = (se_loc) % chunkWidth > (location + chunkWidth) % chunkWidth && se_loc < tiles->size() ? tiles->at(se_loc) : nullptr;
		// south
		neighbourTiles[4] = (location + chunkWidth) < tiles->size() ? tiles->at(location + chunkWidth) : nullptr;
		interactableTiles[2] = neighbourTiles[4];
		// south-west
		auto sw_loc = location + chunkWidth - 1;
		neighbourTiles[5] = (sw_loc) % chunkWidth < (location + chunkWidth) % chunkWidth && sw_loc < tiles->size() ? tiles->at(sw_loc) : nullptr;
		// west
		neighbourTiles[6] = ((location - 1) % chunkWidth) < (location % chunkWidth) ? tiles->at(location - 1) : nullptr;
		interactableTiles[3] = neighbourTiles[6];
		// north-west
		auto nw_loc = location - chunkWidth - 1;
		neighbourTiles[7] = (nw_loc) % chunkWidth < (location - chunkWidth) % chunkWidth && nw_loc >= 0 ? tiles->at(nw_loc) : nullptr;
	}

	void TileMap::drawChunks(BaseGame* game) {
		currentChunk->draw(game);
		for (auto chunk : visibleChunks) {
			if (chunk) {
				chunk->draw(game);
			}
		}
	}

	bool TileMap::isChunkInDirection(int direction) {
		return currentChunk->neighbours[direction] != nullptr;
	}

	TileMap::~TileMap() { }

}