#pragma once

#include "Tile.h"
#include "Chunk.h"
#include <vector>

namespace ChunkMapEngine {
	class BaseGame;

	/// the TileMap class contains and manages all Chunks
	class TileMap
	{
	public:
		~TileMap();
		TileMap(int chunkWidth, int chunkHeight);

		/// checks if the currentChunk is still valid, else it updates the currentChunk and the list of rendered Chunks.
		void updateChunks();
		/// checks if the currentTile is still valid, else it updates the currentTile and its neighbours.
		void updateTiles();
		/// defines the neighbours of the currentTile based on its location inside the Chunk.
		void setTiles(int location);
		/// draws all visible Chunks.
		void drawChunks(BaseGame* game);
		/// checks if there is already a Chunk in the given direction.
		bool isChunkInDirection(int direction);

		std::shared_ptr<Chunk> getCurrentChunk() { return currentChunk; }
		std::shared_ptr<Tile> getInteractableTile(int direction) { return interactableTiles[direction]; }

		/// override and use to create a unique starting area for the game world.
		virtual void initializeStartingRegion(BaseGame* game, Entity* player, int type) { }
		/// override to define how the TileMap should be expanded if possible.
		virtual void expandMap(BaseGame* game, int direction) { }
		/// override to define how neighbouting but seperated Chunks could be connected, allowing traversal between the Chunks if necessary. (for Example by removing colliders)
		virtual void connectChunks(BaseGame* game, int direction) { }

	protected:
		int chunkWidth;
		int chunkHeight;
		/// an Entity representing the player.
		Entity* player;
		/// the Chunk the player Entity is currentyl located in.
		std::shared_ptr<Chunk> currentChunk;
		std::vector<std::shared_ptr<Chunk>> chunks;
		/// a list of all non-culled Chunks
		std::vector<std::shared_ptr<Chunk>> visibleChunks;
		/// the index of the tile the player Entity is currently located on. 
		int currentTileLocation = 0;
		/// the tile the player Entity is currently located on.
		std::shared_ptr<Tile> currentTile;
		/// array of the eight neighbouring Tiles to the currentTile, ordered clockwise from north to northwest.
		std::array<std::shared_ptr<Tile>, 8> neighbourTiles = {
			nullptr, // 0 = north
			nullptr, // 1 = northeast
			nullptr, // 2 = east
			nullptr, // 3 = southeast
			nullptr, // 4 = south
			nullptr, // 5 = southwest
			nullptr, // 6 = west
			nullptr	 // 7 = northwest
		};
		/// array of the four neighbouring Tiles that the player Entity would be able to interact with.
		std::array<std::shared_ptr<Tile>, 4> interactableTiles = { nullptr };
	};
}