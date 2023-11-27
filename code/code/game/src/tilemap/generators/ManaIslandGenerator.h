#pragma once

#include "IslandGenerator.h"

namespace WorldExtender {
	class ManaIslandGenerator : public IslandGenerator {
	public:
		ManaIslandGenerator() : IslandGenerator() { };
		std::vector<int> generateChunk() override;
		std::vector<int> defineTileVersions(std::vector<int> island) override;
	};
}