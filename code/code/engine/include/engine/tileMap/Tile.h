#pragma once

#include "engine/tileMap/Area.h"
#include "engine/entities/Entity.h"
#include "engine/Settings.h"
#include <vector>

namespace ChunkMapEngine {
	/// struct for handling the vertices and indices needed by Tile for correct rendering
	struct glData {
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
	};

	/// Tile represents the smallest subset of a TileMap, providing interactions, obstacles in form of physic bodies, graphics and the data behind the game world. Inheriting Area allows to check if an Entity is currently inside the Tile.
	class Tile : public Entity, public Area
	{
	public:
		Tile(BaseGame* game, Texture texture, int type, int version, glm::vec3 position = glm::vec3(0, 0, 0), float size = 1, int orientation = ChunkMapEngine::NULL_DIR);

		/// draws the Tile on the screen
		void draw(BaseGame* game) override;
		void startContact() override;
		/// completely removes the collider from the Tile. Useful when replacing the Tile.
		void removeCollider(b2World* physicsWorld) override;
		/// returns the Tile's type.
		int getType() { return type; };
		/// returns the Tile's orientation.
		int getOrientation() { return orientation; }
		/// returns if the Tile is interactable or not.
		bool isInteractable() { return interactable; };
		/// changes the rendere version of the Tile.
		void changeVersion(int newVersion);

		/// override to define a unique behavior.
		virtual void reset() { }
		/// override to define a unique behavior when interacting with the Tile.
		virtual void interact() { }
	protected:
		int type;
		int version;
		int orientation;
		bool interactable = false;
		int resourceCount = 0;

		/// calculates the vertices for the Mesh based on the Tile's type, version and the used Texture. 
		glData getTileVertices(int type, int version, Texture* texture);
		/// creates a new physics body in case the Tile if collision  is required.
		b2Body* createBody(BaseGame* game, b2Vec2 position, float size, Tile* tile);
	};
}