
#include "engine/physics/ContactListener.h"
#include "engine/entities/Entity.h"

namespace ChunkMapEngine {
    void ContactListener::BeginContact(b2Contact *contact) {
        auto bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
        auto bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
        Entity* A = nullptr;
        Entity* B = nullptr;

        //check if fixture A was a ball
        if (bodyUserDataA) {
            A = (Entity*) bodyUserDataA;
        }

        //check if fixture B was a ball
        if (bodyUserDataB) {
            B = (Entity*) bodyUserDataB;
        }

        if(A)
            A->startContact();

        if(B)
            B->startContact();
    }

    void ContactListener::EndContact(b2Contact *contact) {

    }
}