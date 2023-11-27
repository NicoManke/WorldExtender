#include "engine/rendering/Animator.h"
#include "engine/Settings.h"

namespace ChunkMapEngine {
	Animator::Animator(Mesh* mesh, Texture* texture) {
		this->mesh = mesh;
		this->texture = texture;
	}

    void Animator::resetElapsedTime() {
        elapsedAnimationTime = 0.0f;
    }

    void Animator::updateAnimation(int animation) {
        this->currentAnimation = animation;
    }

    void Animator::updateFrame(int frame) {
        this->currentFrame = frame;
    }

    void Animator::setUncancellablePlaying(bool state) { 
        isUncancellablePlaying = state; 
    }

    void Animator::startUncancellableAnimation() {
        updateFrame(0);
        resetElapsedTime();
        setUncancellablePlaying(true);
    }

    void Animator::animate(float deltaTime, Mesh* mesh, Texture* texture) {
        elapsedAnimationTime += deltaTime;

        int frameCount = texture->getFrameCount(currentAnimation);
        auto animDur = texture->getAnimationDuration(currentAnimation);
        float frameDuration = animDur / frameCount;

        currentFrame = static_cast<int>(elapsedAnimationTime / frameDuration) % frameCount;

        if (elapsedAnimationTime >= animDur) {
            elapsedAnimationTime -= animDur;
            if (isUncancellablePlaying == true) {
                isUncancellablePlaying = false;
            }
        }

        mesh->updateMesh(getAnimatedVertices(currentAnimation, currentFrame));
    }

	void Animator::animate(float deltaTime) {
        animate(deltaTime, mesh, texture);
	}

    std::vector<float> Animator::getAnimatedVertices(int animation, int frame, Texture* texture) {
        // inverse animation index
        animation = (texture->getAnimationCount() - 1 - animation) % texture->getAnimationCount();
        auto width = texture->getWidth();
        auto height = texture->getHeight();
        auto right = (SPRITE_SIZE + SPRITE_SIZE * frame) / width;
        auto left = (SPRITE_SIZE * frame) / width;
        auto top = (SPRITE_SIZE + SPRITE_SIZE * animation) / height;
        auto bottom = (SPRITE_SIZE * animation) / height;
        std::vector<float> newData = {
            // positions          // texture coords
            0.5f, 0.5f, 0.0f,     right, top,    // top right
            0.5f, -0.5f, 0.0f,    right, bottom, // bottom right
            -0.5f, -0.5f, 0.0f,   left,  bottom, // bottom left
            -0.5f, 0.5f, 0.0f,    left,  top     // top left
        };
        return newData;
    }

    std::vector<float> Animator::getAnimatedVertices(int animation, int frame) {
        return getAnimatedVertices(animation, frame, texture);
    }
}