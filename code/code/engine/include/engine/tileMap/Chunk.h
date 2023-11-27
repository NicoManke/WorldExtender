#pragma once

#include "Area.h"
#include "Tile.h"
#include "Generator.h"
#include <memory>
#include <vector>

namespace ChunkMapEngine {
	/// Chunk functions as subsets of the whole TileMap and contains the Tile objects the game world is build from. Inheriting Area allows to check if an Entity is currently inside the Chunk.
	class Chunk : public Area {
	public:
		Chunk(int x, int y, int rowsCount, int columnsCount);
		~Chunk();
		/// draws the chunk by drawing all contained tiles.
		virtual void draw(BaseGame* game);
		/// override to determine how the Chunk is generated.
		virtual void generate() { }
		/// override to add logic for connected tiles based on the Chunk's layout.
		virtual void variate() { }
		/// override to determine how the Chunk's Tiles are added to the Chunk object.
		virtual void populate(int type, BaseGame* game) { }
		virtual std::vector<std::shared_ptr<Tile>>* getTiles() { return &tiles; }
		/// returns the Chunk's artificial X position in relation to other Chunks in the TileMap.
		float getX() { return center.x; }
		/// returns the Chunk's artificial Y position in relation to other Chunks in the TileMap.
		float getY() { return center.y; }
		/// (de)activates the colliders of contained tiles. Can be used to turn off collisions or decreasing computational costs.
		void cullColliders(bool culled);

		/// array of the eight neighbouring Chunks, ordered clockwise from north to northwest.
		std::array<std::shared_ptr<Chunk>, 8> neighbours = { 
			nullptr, // 0 = north
			nullptr, // 1 = northeast
			nullptr, // 2 = east
			nullptr, // 3 = southeast
			nullptr, // 4 = south
			nullptr, // 5 = southwest
			nullptr, // 6 = west
			nullptr	 // 7 = northwest
		};
	protected:
		std::vector<std::shared_ptr<Tile>> tiles;
		/// all contained Tiles that have a collider.
		std::vector<std::shared_ptr<Tile>> switchColliderTiles;
		Generator* generator;
		glm::vec2 center;
	private:
		int rows = 0;
		int columns = 0;
	};
}