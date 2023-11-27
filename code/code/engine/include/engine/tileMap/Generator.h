#pragma once

#include <vector>

namespace ChunkMapEngine {
	/// Generator functions as an template for other Generator classes each implementing a unique generating approach. Enabling different Chunk layouts without the need of different Chunk sub-classes.
	class Generator {
	public:
		Generator(int size) {
			this->size = size;
		}

		/// override to generate a unique Chunk layout. 
		virtual std::vector<int> generateChunk() { return std::vector<int>(size, 0); };
		/// override to decide which version of a Tile texture should be used to create the illusion of connected textures based on the Chunk's layout.
		virtual std::vector<int> defineTileVersions(std::vector<int> island) { return std::vector<int>(size, 0); };

		/// generates a random number based on the given range. 
		short randomRange(short min, short max);

	protected:
		int size = 0;
	};
}