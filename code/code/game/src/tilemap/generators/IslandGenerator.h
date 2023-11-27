#pragma once

#include "engine/tileMap/Generator.h"
#include "../../Parameters.h"

namespace WorldExtender {
	class IslandGenerator : public ChunkMapEngine::Generator {
	public:
		IslandGenerator() : Generator(WIDTH * HEIGHT) { };
		std::vector<int> generateChunk() override;
		std::vector<int> defineTileVersions(std::vector<int> island) override;
	protected:
		int decideGroundVersion(int topType, int bottomType, int leftType, int rightType);
		std::vector<int> defaultLayout();
	};
}