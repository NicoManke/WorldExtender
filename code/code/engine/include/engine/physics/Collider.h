#pragma once

#include <box2d/box2d.h>

namespace ChunkMapEngine {
	/// Collider functions as a component that gives its owner a physical body and its properties
	class Collider {
	public:
		Collider() { };
		Collider(b2Body* body);
		~Collider();
		/// simply returns a reference to a pointer of the physics body.
		b2Body*& getBody() { return body; }
		/// returns the physics body in a managed manner, so it can be correctly destroyed by b2World's DestroyBody(...).
		b2Body*& destroyBody();
		void startContact();
		/// activates and deactivates the Entity's physics body based on the parsed bool. Can be used to decrease computational costs.
		void setBodyActive(bool active);
	private:
		b2Body* body = nullptr;
	};
}