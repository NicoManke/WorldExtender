#pragma once

#include "glm/vec2.hpp"
#include <memory>
#include <array>

namespace ChunkMapEngine {
	class BaseGame;

	/// the Area class allows simple is-point-in-area checks for objects that represent a 2D area inside the game world.
	class Area {
	public:
		Area() { };
		/// creating an Area object based the given x and y coords. "tl" stands for top-left. "br" stands for bottom-right.
		Area(int tl_x, int tl_y, int br_x, int br_y);
		/// checks if a point representes by the given vector is inside this Area.
		virtual bool containsPoint(const glm::vec2& point) const;
		/// checks if a point representes by the given x and y values is inside this Area.
		virtual bool containsPoint(float x, float y) const;

		glm::vec2 m_topLeft;
		glm::vec2 m_bottomRight;
	};
}