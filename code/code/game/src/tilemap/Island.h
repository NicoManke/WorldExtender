#pragma once

#include "engine/tileMap/Chunk.h"
#include "../Parameters.h"

namespace WorldExtender {
	class Island : public ChunkMapEngine::Chunk {
	public:
		Island(ChunkMapEngine::BaseGame* game, int type, int xOffset, int yOffset);
		~Island() { };
		void generate() override;
		void variate() override;
		void populate(int type, ChunkMapEngine::BaseGame* game) override;
	private:
		std::vector<int> layout;
		std::vector<int> versions;
		int type;
	};
}