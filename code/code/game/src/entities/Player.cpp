#include "Player.h"
#include "../Game.h"
#include "engine/Assets.h"
#include <iostream>

namespace WorldExtender {
    struct glData {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };

    glData getVertices() {
        glData meshData;

        meshData.vertices = {
            // positions          // texture coords
            0.5f,  0.5f, 0.0f,    1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,    1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left
        };

        meshData.indices = {
            0, 1, 3,
            1, 2, 3
        };

        return meshData;
    }

    float squarePoints = 0.4f;

    struct userData : b2BodyUserData {
        int a = 12;
    };

    b2Body* createPlayer(ChunkMapEngine::BaseGame* game, b2Vec2 position, float size, Player* player) {
        b2BodyDef bodyDef;
        // User Data
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(player);
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = position;
        b2Body* body = game->getPhysicsWorld()->CreateBody(&bodyDef);
        auto halfSide = 0.25f;
        b2Vec2 vertices[6];
        vertices[0].Set(halfSide, halfSide);
        vertices[1].Set(halfSide, 0.0f);
        vertices[2].Set(halfSide, -halfSide);
        vertices[3].Set(-halfSide, -halfSide);
        vertices[4].Set(-halfSide, 0.0f);
        vertices[5].Set(-halfSide, halfSide);
        for (auto& point : vertices) {
            point *= size;
        }
        b2PolygonShape boxShape;
        boxShape.Set(vertices, 6);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.density = 1;
        fixtureDef.friction = 0.1f;
        fixtureDef.restitution = 0.1f;
        body->CreateFixture(&fixtureDef);
        body->SetFixedRotation(true);
        return body;
    }

    Player::Player(ChunkMapEngine::BaseGame* game, ChunkMapEngine::Texture texture, glm::vec3 position, float scale) : Entity(
        texture,
        ChunkMapEngine::Shader("shaders/playerShader.vert", "shaders/playerShader.frag"),
        ChunkMapEngine::Mesh(getVertices().vertices,
             getVertices().indices
        ),
        position,
        0.0f,
        scale) {

        animator = ChunkMapEngine::Animator(&this->mesh, &this->texture);
        collider = ChunkMapEngine::Collider(createPlayer(game, { position.x, position.y }, scale, this));

        inventory = Inventory();
        walkingSound = make_shared<SoLoud::Wav>();
        walkingSound->load(ChunkMapEngine::resolveAssetPath("audio/walking.mp3").string().c_str());
        walkingSound->setSingleInstance(true);
        walkingSound->setLooping(true);
        walkingSoundHandle = game->getAudioSystem()->play(*walkingSound, -1.0f, 0.0f, true);
    }

    Player::~Player() {
        walkingSound.reset();
    }

    void Player::update(ChunkMapEngine::BaseGame* game, float deltaTime) {
        auto window = game->getWindow();
        auto body = collider.getBody();
        b2Vec2 direction{ 0.0f, 0.0f };
        auto angle = body->GetAngle();

        isInteracting = animator.IsUncancellablePlaying();

        if (isInteracting == false) {

            if (glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS
                && glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS
                && glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS
                && glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS) {
                // add logic and Assets for directional idle, like:
                // switch (turnDirection) {
                // case ChunkMapEngine::NORTH:
                //     animator.updateanimation(...);
                //     break;
                // case ...:
                //      ...
                //      break;
                // }
                animator.updateAnimation(0);
                game->getAudioSystem()->setPause(walkingSoundHandle, true);
            }
            else {
                game->getAudioSystem()->setPause(walkingSoundHandle, false);

                if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                    direction = defineDirection(1, -1, ChunkMapEngine::SOUTH_EAST, 5);
                }
                else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                    direction = defineDirection(-1, -1, ChunkMapEngine::SOUTH_WEST, 6);
                }
                else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                    direction = defineDirection(-1, 1, ChunkMapEngine::NORTH_WEST, 7);
                }
                else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                    direction = defineDirection(1, 1, ChunkMapEngine::NORTH_EAST, 8);
                }
                else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                    direction = defineDirection(1, 0, ChunkMapEngine::EAST, 3);
                }
                else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                    direction = defineDirection(0, -1, ChunkMapEngine::SOUTH, 1);
                }
                else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                    direction = defineDirection(-1, 0, ChunkMapEngine::WEST, 4);
                }
                else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                    direction = defineDirection(0, 1, ChunkMapEngine::NORTH, 2);
                }
            }
        }

        isInteracting = animator.IsUncancellablePlaying();

        // Apply velocity
        b2Vec2 vel{ direction.x, direction.y };
        vel.Normalize();
        vel *= deltaTime * translationSpeed;
        body->SetLinearVelocity(vel);

        game->updateCamPos(position); 
    }

    void Player::draw(ChunkMapEngine::BaseGame* game) {
        auto body = collider.getBody();
        auto physicsPos = body->GetPosition();

        position.x = physicsPos.x;
        position.y = physicsPos.y;
        zRotation = body->GetAngle();

        auto mvpMatrix = game->calculateMvpMatrix(position, zRotation, scale);
        shader.use();
        shader.setMatrix("playerMVP", mvpMatrix);
        texture.bind();
        mesh.draw();

        inventory.draw(game);
    }

    void Player::animate(float deltaTime) {
        animator.animate(deltaTime);
    }

    void Player::startContact() {
        collider.startContact();
    }

    void Player::interact(bool isInteractableTile, int type) {
        if (isInteractableTile == false) { 
            return; 
        }
        switch (type) {
        case MANA:
            inventory.increaseManaCount();
            break;
        case STONE:
            inventory.increaseStoneCount();
            break;
        case BUSH:
            inventory.increaseWoodCount();
            break;
        }
    }

    void Player::setInteracting(bool state) {
        isInteracting = state;
    }

    void Player::startInteractionAnimation() {
        isInteracting = true;

        if (animator.IsUncancellablePlaying() == false) {
            animator.startUncancellableAnimation();

            switch (turnDirection) {
            case ChunkMapEngine::NORTH:
                animator.updateAnimation(10);
                break;
            case ChunkMapEngine::EAST:
            case ChunkMapEngine::NORTH_EAST:
                animator.updateAnimation(11);
                break;
            case ChunkMapEngine::SOUTH:
            case ChunkMapEngine::SOUTH_EAST:
            case ChunkMapEngine::SOUTH_WEST:
                animator.updateAnimation(9);
                break;
            case ChunkMapEngine::WEST:
            case ChunkMapEngine::NORTH_WEST:
                animator.updateAnimation(12);
                break;
            default:
                animator.updateAnimation(9);
                break;
            }
        }
    }

    b2Vec2 Player::defineDirection(float xVelocity, float yVelocity, int turnDirection, int animation) {
        this->turnDirection = turnDirection;
        animator.updateAnimation(animation);
        return b2Vec2{ xVelocity, yVelocity };
    }
}
