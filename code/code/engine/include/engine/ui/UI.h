#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "../rendering/Texture.h"
#include "../rendering/Mesh.h"
#include "../rendering/Shader.h"

namespace ChunkMapEngine {
	class BaseGame;

	/// the Icon struct represents the position of a single UI sprite on a texture atlas/sprite sheet. Uses 32px as oofset.
	struct Icon {
		int row;
		int column;
	};

	/// the UI class provides a simple object representation including mesh and texture. Icon, ratio and the fullSize bool parameter simplify the presentation management of the rendered images.
	class UI {
	public:
		/// @brief creates a new mesh with a texture functioning as UI.
		/// @param icon defines the position of the used sub-texture/sprite on the loaded image.
		/// @param ratio allows stretching the used texture in the respective dimension.
		/// @param fullSize if true, the UI will ignore the 32px offset and renders the whole loaded image. Usefull for fullscreens etc.
		UI(Texture texture, 
			Icon icon,
			glm::vec2 ratio,
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			float zRotation = 0.0f,
			float scale = 1.0f,
			bool fullSize = false);
		~UI();
		/// draws the UI element to the screen based on its mesh and texture.
		void draw(BaseGame* game);
		void setPosition(const glm::vec3& position) { this->position = position; }
		void setZRotation(float zRotation) { this->zRotation = zRotation; }
		void setScale(const glm::vec3& scale) { this->scale = scale; }
		/// renders every the UI element with an offset, without transforming titshe actual location.
		void moveUI(const glm::vec2& relativePosition);
		/// changes the displayed UI Icon based on the new Icon's location on the atlas.
		void changeIcon(Icon newIcon);
	private:
		Texture texture;
		Shader shader;
		Mesh mesh;
		float zRotation;
		bool fullSize;
		glm::vec2 ratio;
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec2 relPos;
	};
}