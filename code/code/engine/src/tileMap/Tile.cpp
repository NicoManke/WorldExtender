#include <iostream>
#include "engine/tileMap/Tile.h"
#include "engine/BaseGame.h"
#include "engine/Settings.h"

namespace ChunkMapEngine {

    Tile::Tile(BaseGame* game, Texture texture, int type, int version, glm::vec3 position, float size, int orientation) :
        Entity(
            texture,
            Shader("shaders/textureVertShader.vert", "shaders/textureFragShader.frag"),
            Mesh(getTileVertices(type, version, &texture).vertices, getTileVertices(type, version, &texture).indices),
            position,
            0,
            size
        )
        , Area(
            position.x - 0.5 * SCALING,
            position.y + 0.5 * SCALING,
            position.x + 0.5 * SCALING,
            position.y - 0.5 * SCALING
        )
    {
        this->type = type;
        this->version = version;
        this->orientation = orientation;
    }

    glData Tile::getTileVertices(int type, int version, Texture* texture) {
        glData tileData;
        // logic for texture atlas
        auto width = texture->getWidth();
        auto height = texture->getHeight();
        auto rows = (int)(height / SPRITE_SIZE);
        type = (rows - 1 - type) % rows;
        float left = (version * SPRITE_SIZE) / width;
        float right = ((SPRITE_SIZE + version * SPRITE_SIZE) - 0.01) / width;
        float top = ((SPRITE_SIZE + SPRITE_SIZE * type) - 0.01) / height;
        float bottom = (SPRITE_SIZE * type) / height;
        tileData.vertices = {
            // positions         // texture coords
            0.5f,  0.5f, 0.0f,   right, top,      // top right
            0.5f, -0.5f, 0.0f,   right, bottom,   // bottom right
            -0.5f, -0.5f, 0.0f,  left, bottom,    // bottom left
            -0.5f,  0.5f, 0.0f,  left, top        // top left
        };

        tileData.indices = {
            0, 1, 3,
            1, 2, 3
        };

        return tileData;
    }

    b2Body* Tile::createBody(BaseGame* game, b2Vec2 position, float size, Tile* tile) {
        b2BodyDef bodyDef;
        // User Data
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(tile);
        bodyDef.type = b2_staticBody;
        bodyDef.position = position;
        b2Body* body = game->getPhysicsWorld()->CreateBody(&bodyDef);

        b2PolygonShape squareShape;
        squareShape.SetAsBox(size, size);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &squareShape;
        fixtureDef.density = 0;
        fixtureDef.friction = 0.0f;
        fixtureDef.restitution = 0.0f;
        body->CreateFixture(&fixtureDef);

        return body;
    }

    void Tile::draw(BaseGame* game) {
        auto mvpMatrix = game->calculateMvpMatrix(position, 0, scale);
        shader.use();
        shader.setMatrix("mvp", mvpMatrix);
        texture.bind();
        mesh.draw();
    }

    void Tile::startContact() {
        if (hasCollider) {

        }
    }

    void Tile::removeCollider(b2World* physicsWorld) {
        auto temp = collider.destroyBody();
        if (temp != nullptr) {
            physicsWorld->DestroyBody(temp);
        }
        collider = {};
        hasCollider = false;
    }

    void Tile::changeVersion(int newVersion) {
        version = newVersion;
        mesh.updateMesh(getTileVertices(type, newVersion, &texture).vertices);
    }
}