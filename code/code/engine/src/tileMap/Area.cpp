#include "engine/tileMap/Area.h"

namespace ChunkMapEngine {
	Area::Area(int tl_x, int tl_y, int br_x, int br_y) {
		m_topLeft = glm::vec2(tl_x, tl_y);
		m_bottomRight = glm::vec2(br_x, br_y);
	}

	bool Area::containsPoint(const glm::vec2& point) const {
		auto check = point.x >= m_topLeft.x
			&& point.x <= m_bottomRight.x
			&& point.y <= m_topLeft.y
			&& point.y >= m_bottomRight.y;
		return check;
	}

	bool Area::containsPoint(float x, float y) const {
		auto point = glm::vec2(x, y);
		return containsPoint(point);
	}
}