#pragma once

#include "Texture.h"
#include "Mesh.h"
#include <vector>

namespace ChunkMapEngine {
	/// Animator animates the textures of Entities by iterating over given texture atlasis by transforming the mesh's texture coordinates.
	class Animator {
	public:
		Animator() { };
		Animator(Mesh* mesh, Texture* texture);
		/// plays the animation defined animation. Can be used if the animator did not recieve a pointer to mesh and texture. Allows using a different Texture.
		void animate(float deltaTime, Mesh* mesh, Texture* texture);
		/// plays the animation defined animation.
		void animate(float deltaTime);
		/// resets the elapsed animation time. Causes the next animation to start with its first frame.
		void resetElapsedTime();
		/// forces the animation to jump to a given frame.
		void updateFrame(int frame);
		/// sets the animation that should be played.
		void updateAnimation(int animation);
		/// returns the information if the animator is currently playing an unskippable animation.
		bool IsUncancellablePlaying() { return isUncancellablePlaying; };
		/// updates the state, if an animation is skippable or not.
		void setUncancellablePlaying(bool state);
		/// plays an unskippable animation beginning with its first frame.
		void startUncancellableAnimation();
	private:
		/// calculates the vertices containing the texture coordinates for animating the Entity based on the current animation and frame. Allows using a different Texture.
		std::vector<float> getAnimatedVertices(int animation, int frame, Texture* texture);
		/// calculates the vertices containing the texture coordinates for animating the Entity based on the current animation and frame
		std::vector<float> getAnimatedVertices(int animation, int frame);
		float elapsedAnimationTime = 0.0f;
		int currentAnimation = 0;
		int currentFrame = 0;

		bool isUncancellablePlaying = false;

		Mesh* mesh = nullptr;
		Texture* texture = nullptr;
	};
}