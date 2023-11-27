#pragma once

#include "IslandGenerator.h"

namespace WorldExtender {
	class PortalIslandGenerator : public IslandGenerator {
	public:
		PortalIslandGenerator() : IslandGenerator() { };
		std::vector<int> generateChunk() override;
		std::vector<int> defineTileVersions(std::vector<int> island) override;
	protected:
		int decideBrickVersion(int topType, int bottomType, int leftType, int rightType);
		int decidePortalVersion(int topType, int bottomType, int leftType, int rightType);
	};
}