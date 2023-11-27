#include "IslandGenerator.h"
#include <array>

namespace WorldExtender {
	std::vector<int> IslandGenerator::generateChunk() {
		std::vector<int> island(WIDTH * HEIGHT, 0);
		island = defaultLayout();

		auto topEntry = (short)(WIDTH * 1.5);
		auto leftEntry = (short)(WIDTH * ((HEIGHT - 1) * 0.5) + 1);
		auto rightEntry = (short)(WIDTH * ((HEIGHT + 1) * 0.5) - 2);
		auto bottomEntry = (short)(WIDTH * (HEIGHT - 1) - (0.5 * WIDTH));
		island[topEntry] = PRE_BRIDGE;
		island[leftEntry] = PRE_BRIDGE;
		island[rightEntry] = PRE_BRIDGE;
		island[bottomEntry] = PRE_BRIDGE;

		// artefacts
		int obstacleCount = 0;
		std::array<int, 3> previousPos = { -1 };

		while (obstacleCount < 4) {
			int position = 0;
			int obstacleType = 0;
			short randHeight = randomRange(1, HEIGHT - 2);
			short randWidth = randomRange(1, WIDTH - 2);
			position = randWidth + randHeight * WIDTH;
			
			// keep bridge entries free 
			if (position == topEntry || position == leftEntry || position == rightEntry || position == bottomEntry) {
				continue;
			}
			auto continueLoop = false;
			for each (int pos in previousPos) {
				if (position == pos) {
					continueLoop = true;
					break;
				}
			}
			if (continueLoop) {
				continue;
			}

			if (obstacleCount == 0) {
				obstacleType = STONE;
				previousPos[0] = position;
			}
			else if (obstacleCount == 1) {
				obstacleType = BUSH;
				previousPos[1] = position;
			}
			else if (obstacleCount == 2) {
				obstacleType = MANA;
				previousPos[2] = position;
			}
			else {
				obstacleType = randomRange(STONE, BUSH);
			}
			island[position] = obstacleType;
			obstacleCount++;
		}

		return island;
	}

	std::vector<int> IslandGenerator::defineTileVersions(std::vector<int> island) {
		std::vector<int> versionedIsland(size, 0);

		for (int i = 0; i < WIDTH * HEIGHT; i++) {
			auto version = 0;
			auto type = island[i];
			auto left = i - 1;
			auto right = i + 1;
			auto top = i - WIDTH;
			auto bottom = i + WIDTH;

			switch (type) {
			case VOIDS:
				if (top >= 0) {
					switch (island[top]) {
					case VOIDS:
						version = 0;
						break;
					default:
						if (island[top - 1] == VOIDS && island[top + 1] != VOIDS) { version = 1; }
						else if (island[top - 1] != VOIDS && island[top + 1] != VOIDS) { version = 2; }
						else { version = 3; }
						break;
					}
				}
				else {
					version = 0;
				}
				break;
			case GRASS:
				version = decideGroundVersion(island[top], island[bottom], island[left], island[right]);
				break;
			case MANA:
				version = decideGroundVersion(island[top], island[bottom], island[left], island[right]);
				break;
			case STONE:
				version = decideGroundVersion(island[top], island[bottom], island[left], island[right]);
				break;
			case BUSH:
				version = decideGroundVersion(island[top], island[bottom], island[left], island[right]);
				break;
			case PRE_BRIDGE:
				if (island[top] == VOIDS) {
					version = 4;
				}
				else if (island[bottom] == VOIDS) {
					version = 7;
				}
				else if (island[left] == VOIDS) {
					version = 5;
				}
				else if (island[right] == VOIDS) {
					version = 6;
				}
				break;
			default:
				break;
			}
			versionedIsland[i] = version;
		}

		return versionedIsland;
	}

	std::vector<int> IslandGenerator::defaultLayout() {
		std::vector<int> defaultIsland(size, 0);

		for (int i = 0; i < WIDTH; i++) {
			defaultIsland[i] = VOIDS;
		}
		for (int i = WIDTH * (HEIGHT - 1); i < HEIGHT * WIDTH; i++) {
			defaultIsland[i] = VOIDS;
		}
		for (int i = 0; i < WIDTH * HEIGHT; i += WIDTH) {
			defaultIsland[i] = VOIDS;
		}
		for (int i = WIDTH - 1; i < WIDTH * HEIGHT; i += WIDTH) {
			defaultIsland[i] = VOIDS;
		}

		for (int i = 1; i < HEIGHT - 1; i++) {
			for (int j = 1; j < WIDTH - 1; j++) {
				auto cell = j + i * WIDTH;
				defaultIsland[cell] = GRASS;
			}
		}

		return defaultIsland;
	}

	int IslandGenerator::decideGroundVersion(int topType, int bottomType, int leftType, int rightType) {
		auto version = 0;

		if (topType != VOIDS && bottomType != VOIDS && leftType != VOIDS && rightType != VOIDS) {
			if (bottomType == BRIDGE) {
				version = 7;
			}
			else {
				version = 0;
			}
		}
		else if (topType == VOIDS && bottomType != VOIDS && leftType != VOIDS && rightType != VOIDS) {
			version = 2;
		}
		else if (topType == VOIDS && bottomType != VOIDS && leftType == VOIDS && rightType != VOIDS) {
			version = 1;
		}
		else if (topType == VOIDS && bottomType != VOIDS && leftType != VOIDS && rightType == VOIDS) {
			version = 3;
		}
		else if (topType != VOIDS && bottomType == VOIDS && leftType != VOIDS && rightType != VOIDS) {
			version = 7;
		}
		else if (topType != VOIDS && bottomType == VOIDS && leftType == VOIDS && rightType != VOIDS) {
			version = 6;
		}
		else if (topType != VOIDS && bottomType == VOIDS && leftType != VOIDS && rightType == VOIDS) {
			version = 8;
		}
		else if (topType != VOIDS && bottomType != VOIDS && leftType == VOIDS && rightType != VOIDS) {
			version = 4;
		}
		else if (topType != VOIDS && bottomType != VOIDS && leftType != VOIDS && rightType == VOIDS) {
			version = 5;
		}
		return version;
	}
}