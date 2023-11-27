#include "ResourceTile.h"

namespace WorldExtender {
	ResourceTile::ResourceTile(ChunkMapEngine::BaseGame* game, ChunkMapEngine::Texture texture, tile_type type, int version, glm::vec3 position, float size, int orientation) : Tile(game, texture, type, version, position, size, orientation) {
		interactable = true;
		resourceCount = 10;
	}

	void ResourceTile::reset() {
		type = GRASS;
		mesh.updateMesh(getTileVertices(GRASS, version, &texture).vertices);
	}

	void ResourceTile::interact() {
		if (resourceCount > 0) {
			resourceCount -= 1;
		}
		if (resourceCount <= 0) {
			interactable = false;
			reset();
		}
	}
}