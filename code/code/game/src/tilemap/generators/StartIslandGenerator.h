#pragma once

#include "IslandGenerator.h"

namespace WorldExtender {
	class StartIslandGenerator : public IslandGenerator {
	public:
		StartIslandGenerator() : IslandGenerator() { };
		std::vector<int> generateChunk() override;
		std::vector<int> defineTileVersions(std::vector<int> island) override;
	protected:
		int decideDirtVersion(int topType, int bottomType, int leftType, int rightType);
	};
}