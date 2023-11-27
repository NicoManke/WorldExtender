#pragma once

#include <box2d/box2d.h>

namespace ChunkMapEngine {
    /// ContactListener encapsulates b2ContactListener from the box2D library
    class ContactListener : public b2ContactListener{
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
    };

}
