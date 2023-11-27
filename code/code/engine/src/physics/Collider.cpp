#include "engine/physics/Collider.h"

namespace ChunkMapEngine {

	Collider::Collider(b2Body* body) {
		this->body = body;
	}

	b2Body*& Collider::destroyBody() {
		auto temp = body;
		body = nullptr;
		return temp;
	}

	void Collider::startContact() {

	}

	void Collider::setBodyActive(bool active) {
		body->SetAwake(active);
	}

	Collider::~Collider() { 
		
	};
}