#pragma once

#include "IslandGenerator.h"

namespace WorldExtender {
	class PlantIslandGenerator : public IslandGenerator {
	public:
		PlantIslandGenerator() : IslandGenerator() { };
		std::vector<int> generateChunk() override;
		std::vector<int> defineTileVersions(std::vector<int> island) override;
	};
}