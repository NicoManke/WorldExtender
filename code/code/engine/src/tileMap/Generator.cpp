#include "engine/tileMap/Generator.h"
#include "engine/Random.h"

namespace ChunkMapEngine {
	short Generator::randomRange(short min, short max)
	{
		return Random::shortRange(min, max);
	}
}