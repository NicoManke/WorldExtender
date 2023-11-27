#pragma once

namespace ChunkMapEngine {
	typedef int direction;

	constexpr float FOV = 90.0f;
	constexpr float SPRITE_SIZE = 32.0f;
	constexpr float SCALING = 10.0f;
	constexpr float CENTERING = 0.5;

	// directions
	constexpr direction NULL_DIR = -1;
	constexpr direction NORTH = 0;
	constexpr direction NORTH_EAST = 1;
	constexpr direction EAST = 2;
	constexpr direction SOUTH_EAST = 3;
	constexpr direction SOUTH = 4;
	constexpr direction SOUTH_WEST = 5;
	constexpr direction WEST = 6;
	constexpr direction NORTH_WEST = 7;
}