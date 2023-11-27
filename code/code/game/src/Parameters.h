#pragma once

namespace WorldExtender {
	typedef int tile_type;
	typedef int island_type;

	// tiles
	constexpr tile_type EMPTY = 0;
	constexpr tile_type VOIDS = 1;
	constexpr tile_type GRASS = 2;
	constexpr tile_type STONE = 3;
	constexpr tile_type MANA = 4;
	constexpr tile_type BUSH = 5;
	constexpr tile_type BRIDGE = 6;
	constexpr tile_type PRE_BRIDGE = 7;
	constexpr tile_type DIRT = 8;
	constexpr tile_type BRICK = 9;
	constexpr tile_type PORTAL = 10;

	// islands
	constexpr island_type NULL_I = -1;
	constexpr island_type BASE_I = 0;
	constexpr island_type START_I = 1;
	constexpr island_type RED_I = 2;
	constexpr island_type SNOW_I = 3;
	constexpr island_type PLANT_I = 4;
	constexpr island_type STONE_I = 5;
	constexpr island_type MANA_I = 6;
	constexpr island_type PORTAL_I = 7;

	// island pool stages
	constexpr int PLANT_STAGE = 6;
	constexpr int STONE_STAGE = 12;
	constexpr int FINAL_STAGE = 25;

	// islands
	constexpr int WIDTH = 11;
	constexpr int HEIGHT = 9;
	constexpr int ISLAND_OFFSET = 1.1;
}