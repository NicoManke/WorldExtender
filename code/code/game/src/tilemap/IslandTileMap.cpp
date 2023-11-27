#include "IslandTileMap.h"
#include "Island.h"
#include "../Game.h"
#include "../Parameters.h"
#include "engine/Random.h"
#include "engine/Logger.h"
#include <iostream>

namespace WorldExtender {

	IslandTileMap::IslandTileMap() : TileMap(WIDTH, HEIGHT) {
		islandManager = IslandManager();
	};

	void IslandTileMap::initializeStartingRegion(ChunkMapEngine::BaseGame* game, ChunkMapEngine::Entity* player, int type) {
		this->player = player;
		auto island = std::make_shared<Island>(game, START_I, 0, 0);
		chunks.push_back(island);
		currentChunk = std::move(island);
		currentChunk->cullColliders(false);
		auto tiles = currentChunk->getTiles();
		auto playerPos = player->getPosition();
		for (int i = 0; i < tiles->size(); i++) {
			if (tiles->at(i)->containsPoint(playerPos.x, playerPos.y)) {
				setTiles(i);
				break;
			}
		}
	}

	void IslandTileMap::expandMap(ChunkMapEngine::BaseGame* game, int direction) {
		auto otherChunk = currentChunk->neighbours[direction];
		if (otherChunk != nullptr) {
			return;
		}

		auto x = currentChunk->getX();
		auto y = currentChunk->getY();
		glm::vec2 potNeighbour1 = { 0, 0 };
		glm::vec2 potNeighbour2 = { 0, 0 };
		glm::vec2 potNeighbour3 = { 0, 0 };
		switch (direction) {
		case ChunkMapEngine::NORTH:
			y += 1;
			potNeighbour1 = { x - 1, y + 1 };
			potNeighbour2 = { x    , y + 1 };
			potNeighbour3 = { x + 1, y + 1 };
			break;
		case ChunkMapEngine::EAST:
			x += 1;
			potNeighbour1 = { x + 1, y - 1 };
			potNeighbour2 = { x + 1, y     };
			potNeighbour3 = { x + 1, y + 1 };
			break;
		case ChunkMapEngine::SOUTH:
			y -= 1;
			potNeighbour1 = { x - 1, y - 1};
			potNeighbour2 = { x    , y - 1};
			potNeighbour3 = { x + 1, y - 1};
			break;
		case ChunkMapEngine::WEST:
			x -= 1;
			potNeighbour1 = { x - 1, y - 1 };
			potNeighbour2 = { x - 1, y     };
			potNeighbour3 = { x - 1, y + 1 };
			break;
		default:
			return;
		}

		for (std::shared_ptr<ChunkMapEngine::Chunk> chunk : chunks) {
			if (chunk->getX() == x && chunk->getY() == y) {
				std::cout << "There is already an island!" << std::endl;
				currentChunk->neighbours[direction] = chunk;
				chunk->neighbours[(direction + 4) % 8] = currentChunk;
				visibleChunks.push_back(chunk);
				return;
			}
		}

		auto newChunk = islandManager.createIsland(game, x, y);
		currentChunk->neighbours[direction] = newChunk;
		chunks.push_back(newChunk);

		// add already existing chunks to newly created one if neighbour
		newChunk->neighbours[(direction + 2) % 8] = currentChunk->neighbours[(direction + 1) % 8];
		newChunk->neighbours[(direction + 3) % 8] = currentChunk->neighbours[(direction + 2) % 8];
		newChunk->neighbours[(direction + 4) % 8] = currentChunk;
		newChunk->neighbours[(direction + 5) % 8] = currentChunk->neighbours[(direction + 6) % 8];
		newChunk->neighbours[(direction + 6) % 8] = currentChunk->neighbours[(direction + 7) % 8];
		// add the new Chunk to the neighbours of the already existing neighbours of the current Chunk
		auto a = currentChunk->neighbours[(direction + 2) % 8];
		if (a) { a->neighbours[(direction + 7) % 8] = newChunk; }
		auto b = currentChunk->neighbours[(direction + 6) % 8];
		if (b) { b->neighbours[(direction + 1) % 8] = newChunk; }
		auto c = currentChunk->neighbours[(direction + 7) % 8];
		if (c) { c->neighbours[(direction + 2) % 8] = newChunk; }
		auto d = currentChunk->neighbours[(direction + 1) % 8];
		if (d) { d->neighbours[(direction + 6) % 8] = newChunk; }
		// setting new Chunk's corners on the opposit site of the current Chunk
		auto e = newChunk->neighbours[(direction + 6) % 8];
		if (e) { newChunk->neighbours[(direction + 7) % 8] = e->neighbours[direction]; }
		auto f = newChunk->neighbours[(direction + 2) % 8];
		if (f) { newChunk->neighbours[(direction + 1) % 8] = f->neighbours[direction]; }
		// setting new Chunk as neighbour of its direction-opposing corners
		auto g = newChunk->neighbours[(direction + 7) % 8];
		if (g) { g->neighbours[(direction + 3) % 8] = newChunk; }
		auto h = newChunk->neighbours[(direction + 1) % 8];
		if (h) { h->neighbours[(direction + 5) % 8] = newChunk; }
		// depth neighbour check
		for (std::shared_ptr<ChunkMapEngine::Chunk> chunk : chunks) {
			if (chunk->getX() == potNeighbour1.x && chunk->getY() == potNeighbour1.y) {
				newChunk->neighbours[(direction + 7) % 8] = chunk;
				chunk->neighbours[(direction + 3) % 8] = newChunk;
			}
			if (chunk->getX() == potNeighbour2.x && chunk->getY() == potNeighbour2.y) {
				newChunk->neighbours[direction] = chunk;
				chunk->neighbours[(direction + 4) % 8] = newChunk;
			}
			if (chunk->getX() == potNeighbour3.x && chunk->getY() == potNeighbour3.y) {
				newChunk->neighbours[(direction + 1) % 8] = chunk;
				chunk->neighbours[(direction + 5) % 8] = newChunk;
			}
		}

		islandManager.createBridge(game, direction, currentChunk);
		islandManager.createBridge(game, (direction + 4) % 8, newChunk);

		visibleChunks.push_back(currentChunk->neighbours[(direction + 0) % 8]);
	}

	void IslandTileMap::connectChunks(ChunkMapEngine::BaseGame* game, int direction) {
		auto otherChunk = currentChunk->neighbours[direction];
		if (otherChunk == nullptr) {
			return;
		}

		islandManager.createBridge(game, (direction + 4) % 8, otherChunk);
		islandManager.createBridge(game, direction, currentChunk);
	}

	IslandTileMap::~IslandTileMap() { }

}