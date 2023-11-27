#pragma once

#include <vector>
#include <memory>
#include "UI.h"

namespace ChunkMapEngine {
	/// the Canvas class functions as a container for UI objects.
	class Canvas {
	public:
		Canvas();
		/// draws all contained UI elements.
		void draw(BaseGame* game);
		/// adds a new UI element to the Canvas.
		void addUI(std::shared_ptr<UI> ui);
		/// removes every UI element from the Canvas. Useful when using the same Canvas for different ocassions.
		void clearUI();
		/// renders every contained UI element with an offset, without transforming the actual location of the UI element. Taking 2D coordinates.
		void moveUI(glm::vec2 newPosition);
		/// renders every contained UI element with an offset, without transforming the actual location of the UI element. Taking 3D coordinates, but ignoring the z coordinate.
		void moveUI(glm::vec3 newPosition);
	private:
		std::vector<std::shared_ptr<UI>> uiElements;
	};
}