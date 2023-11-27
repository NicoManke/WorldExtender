#include "engine/ui/Canvas.h"

namespace ChunkMapEngine {
	Canvas::Canvas() {
		uiElements = std::vector<std::shared_ptr<UI>>();
	}

	void Canvas::draw(BaseGame* game) {
		for each (auto ui in uiElements) {
			ui->draw(game);
		}
	}

	void Canvas::moveUI(glm::vec3 newPosition) {
		moveUI({ newPosition.x, newPosition.y });
	}

	void Canvas::moveUI(glm::vec2 newPosition) {
		for each (auto ui in uiElements) {
			ui->moveUI(newPosition);
		}
	}

	void Canvas::addUI(std::shared_ptr<UI> ui) {
		uiElements.push_back(ui);
	}


	void Canvas::clearUI() {
		uiElements.clear();
	}
}