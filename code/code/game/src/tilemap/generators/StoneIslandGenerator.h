#pragma once

#include "IslandGenerator.h"

namespace WorldExtender {
	class StoneIslandGenerator : public IslandGenerator {
	public:
		StoneIslandGenerator() : IslandGenerator() { };
		std::vector<int> generateChunk() override;
		std::vector<int> defineTileVersions(std::vector<int> island) override;
	};
}