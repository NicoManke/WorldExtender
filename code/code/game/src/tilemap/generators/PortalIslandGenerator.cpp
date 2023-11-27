#include "PortalIslandGenerator.h"
#include <array>

namespace WorldExtender {
	std::vector<int> PortalIslandGenerator::generateChunk() {
		std::vector<int> island(WIDTH * HEIGHT, 0);
		island = defaultLayout();

		std::array<int, 12> ports = std::array<int, 12>();
		ports[ 1] = (WIDTH * 0.5);
		ports[ 0] = ports[1] - 1;
		ports[ 2] = ports[1] + 1;
		ports[ 5] = (WIDTH * ((HEIGHT - 1) * 0.5));
		ports[ 3] = ports[5] - WIDTH;
		ports[ 7] = ports[5] + WIDTH;
		ports[ 6] = (WIDTH * ((HEIGHT + 1) * 0.5) - 1);
		ports[ 4] = ports[6] - WIDTH;
		ports[ 8] = ports[6] + WIDTH;
		ports[10] = (WIDTH * (HEIGHT) - (0.5 * WIDTH));
		ports[ 9] = ports[10] - 1;
		ports[11] = ports[10] + 1;

		for each (int pos in ports) {
			island[pos] = VOIDS;
		}

		std::array<int, 9> portals = std::array<int, 9>();
		portals[4] = WIDTH * HEIGHT * 0.5;
		portals[3] = portals[4] - 1;
		portals[5] = portals[4] + 1;
		portals[1] = portals[4] - WIDTH;
		portals[0] = portals[1] - 1;
		portals[2] = portals[1] + 1;
		portals[7] = portals[4] + WIDTH;
		portals[6] = portals[7] - 1;
		portals[8] = portals[7] + 1;

		for each (int pos in portals) {
			island[pos] = PORTAL;
		}
		
		std::array<int, 16> frames = std::array<int, 16>();
		auto center = WIDTH * HEIGHT * 0.5;
		frames[ 7] = center - 2;
		frames[ 5] = frames[ 7] - WIDTH;
		frames[ 9] = frames[ 7] + WIDTH;
		frames[ 8] = center + 2;
		frames[ 6] = frames[ 8] - WIDTH;
		frames[10] = frames[ 8] + WIDTH;
		frames[ 2] = center - 2 * WIDTH;
		frames[ 1] = frames[ 2] - 1;
		frames[ 0] = frames[ 2] - 2;
		frames[ 3] = frames[ 2] + 1;
		frames[ 4] = frames[ 2] + 2;
		frames[13] = center + 2 * WIDTH;
		frames[12] = frames[13] - 1;
		frames[11] = frames[13] - 2;
		frames[14] = frames[13] + 1;
		frames[15] = frames[13] + 2;

		for each (int pos in frames) {
			island[pos] = BRICK;
		}


		auto topEntry = ports[2] + WIDTH - 1;
		auto leftEntry = ports[5] + 1;
		auto rightEntry = ports[6] - 1;
		auto bottomEntry = ports[10] - WIDTH;
		island[topEntry] = PRE_BRIDGE;
		island[leftEntry]     = PRE_BRIDGE;
		island[rightEntry]     = PRE_BRIDGE;
		island[bottomEntry] = PRE_BRIDGE;

		// artefacts
		int obstacleCount = 0;
		std::array<int, 1> previousPos = { -1 };

		while (obstacleCount < 2) {
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
			for each (int pos in frames) {
				if (position == pos) {
					continueLoop = true;
					break;
				}
			}
			if (continueLoop) {
				continue;
			}
			for each (int pos in portals) {
				if (position == pos) {
					continueLoop = true;
					break;
				}
			}
			if (continueLoop) {
				continue;
			}
			
			obstacleType = MANA;
			if (obstacleType < previousPos.size()) {
				previousPos[obstacleCount] = position;
			}

			island[position] = obstacleType;
			obstacleCount++;
		}

		return island;
	}

	std::vector<int> PortalIslandGenerator::defineTileVersions(std::vector<int> island) {
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
				else if (island[top] == BRIDGE) {
					version = 0;
				}
				else if (island[bottom] == BRIDGE) {
					version = 3;
				}
				else if (island[left] == BRIDGE) {
					version = 1;
				}
				else if (island[right] == BRIDGE) {
					version = 2;
				}
				break;
			case BRICK:
				version = decideBrickVersion(island[top], island[bottom], island[left], island[right]);
				break;
			case PORTAL:
				version = decidePortalVersion(island[top], island[bottom], island[left], island[right]);
				break;
			default:
				break;
			}
			versionedIsland[i] = version;
		}

		return versionedIsland;
	}

	int PortalIslandGenerator::decideBrickVersion(int topType, int bottomType, int leftType, int rightType) {
		auto version = 0;

		if (topType == BRICK && bottomType == BRICK && leftType == BRICK && rightType == BRICK) {
			version = 0;
		}
		else if (topType != BRICK && bottomType != BRICK && leftType == BRICK && rightType == BRICK) {
			if (bottomType == PORTAL) {
				version = 2;
			}
			else if (topType == PORTAL) {
				version = 7;
			}
		}
		else if (topType != BRICK && bottomType == BRICK && leftType != BRICK && rightType == BRICK) {
			version = 1;
		}
		else if (topType != BRICK && bottomType == BRICK && leftType == BRICK && rightType != BRICK) {
			version = 3;
		}
		else if (topType == BRICK && bottomType != BRICK && leftType == BRICK && rightType == BRICK) {
			version = 7;
		}
		else if (topType == BRICK && bottomType != BRICK && leftType != BRICK && rightType == BRICK) {
			version = 6;
		}
		else if (topType == BRICK && bottomType != BRICK && leftType == BRICK && rightType != BRICK) {
			version = 8;
		}
		else if (topType == BRICK && bottomType == BRICK && leftType != BRICK && rightType != BRICK) {
			if (rightType == PORTAL) {
				version = 4; 
			}
			else if (leftType == PORTAL) {
				version = 5; 
			}
		}
		else if (topType == BRICK && bottomType == BRICK && leftType != BRICK && rightType == BRICK) {
			version = 4;
		}
		else if (topType == BRICK && bottomType == BRICK && leftType == BRICK && rightType != BRICK) {
			version = 5;
		}
		return version;
	}

	int PortalIslandGenerator::decidePortalVersion(int topType, int bottomType, int leftType, int rightType) {
		auto version = 0;

		if (topType == PORTAL && bottomType == PORTAL && leftType == PORTAL && rightType == PORTAL) {
			version = 0;
		}
		else if (topType != PORTAL && bottomType == PORTAL && leftType == PORTAL && rightType == PORTAL) {
			version = 2;
		}
		else if (topType != PORTAL && bottomType == PORTAL && leftType != PORTAL && rightType == PORTAL) {
			version = 1;
		}
		else if (topType != PORTAL && bottomType == PORTAL && leftType == PORTAL && rightType != PORTAL) {
			version = 3;
		}
		else if (topType == PORTAL && bottomType != PORTAL && leftType == PORTAL && rightType == PORTAL) {
			version = 7;
		}
		else if (topType == PORTAL && bottomType != PORTAL && leftType != PORTAL && rightType == PORTAL) {
			version = 6;
		}
		else if (topType == PORTAL && bottomType != PORTAL && leftType == PORTAL && rightType != PORTAL) {
			version = 8;
		}
		else if (topType == PORTAL && bottomType == PORTAL && leftType != PORTAL && rightType == PORTAL) {
			version = 4;
		}
		else if (topType == PORTAL && bottomType == PORTAL && leftType == PORTAL && rightType != PORTAL) {
			version = 5;
		}
		return version;
	}
}