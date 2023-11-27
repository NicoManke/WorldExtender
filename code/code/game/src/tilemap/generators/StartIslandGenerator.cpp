#include "StartIslandGenerator.h"
#include <array>

namespace WorldExtender {
	std::vector<int> StartIslandGenerator::generateChunk() {
		std::vector<int> island(WIDTH * HEIGHT, 0);
		island = defaultLayout();

		std::array<int, 9> dirtSpots = std::array<int, 9>();
		dirtSpots[4] = WIDTH * HEIGHT * 0.5;
		dirtSpots[3] = dirtSpots[4] - 1;
		dirtSpots[5] = dirtSpots[4] + 1;
		dirtSpots[1] = dirtSpots[4] - WIDTH;
		dirtSpots[0] = dirtSpots[1] - 1;
		dirtSpots[2] = dirtSpots[1] + 1;
		dirtSpots[7] = dirtSpots[4] + WIDTH;
		dirtSpots[6] = dirtSpots[7] - 1;
		dirtSpots[8] = dirtSpots[7] + 1;

		for each (int pos in dirtSpots) {
			island[pos] = DIRT;
		}

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
		std::array<int, 4> previousPos = { -1 };

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
			for each (int pos in dirtSpots)
			{
				if (position == pos) {
					continueLoop = true;
					break;
				}
			}
			if (continueLoop) {
				continue;
			}
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

	std::vector<int> StartIslandGenerator::defineTileVersions(std::vector<int> island) {
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
					case BRIDGE:
						version = 4;
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
			case DIRT:
				version = decideDirtVersion(island[top], island[bottom], island[left], island[right]);
				break;
			default:
				break;
			}
			versionedIsland[i] = version;
		}

		return versionedIsland;
	}

	int StartIslandGenerator::decideDirtVersion(int topType, int bottomType, int leftType, int rightType) {
		auto version = 0;

		if (topType == DIRT && bottomType == DIRT && leftType == DIRT && rightType == DIRT) {
			version = 0;
		}
		else if (topType != DIRT && bottomType == DIRT && leftType == DIRT && rightType == DIRT) {
			version = 2;
		}
		else if (topType != DIRT && bottomType == DIRT && leftType != DIRT && rightType == DIRT) {
			version = 1;
		}
		else if (topType != DIRT && bottomType == DIRT && leftType == DIRT && rightType != DIRT) {
			version = 3;
		}
		else if (topType == DIRT && bottomType != DIRT && leftType == DIRT && rightType == DIRT) {
			version = 7;
		}
		else if (topType == DIRT && bottomType != DIRT && leftType != DIRT && rightType == DIRT) {
			version = 6;
		}
		else if (topType == DIRT && bottomType != DIRT && leftType == DIRT && rightType != DIRT) {
			version = 8;
		}
		else if (topType == DIRT && bottomType == DIRT && leftType != DIRT && rightType == DIRT) {
			version = 4;
		}
		else if (topType == DIRT && bottomType == DIRT && leftType == DIRT && rightType != DIRT) {
			version = 5;
		}
		return version;
	}
}