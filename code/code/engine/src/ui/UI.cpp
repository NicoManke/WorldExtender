#include "engine/ui/UI.h"
#include "engine/BaseGame.h"
#include <vector>

namespace ChunkMapEngine {
    struct glData {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };

    glData getUIVertices(Icon icon, Texture* texture, glm::vec2 ration, bool fullSize) {
        glData tileData;
        // logic for texture atlas
        float left = 0.0f;
        float right = 1.0f;
        float top = 1.0f;
        float bottom = 0.0f;
        auto ratiodX = 0.5f * (ration.x / ration.y);
        if (fullSize == false) {
            auto width = texture->getWidth();
            auto height = texture->getHeight();
            auto rows = (int)(height / SPRITE_SIZE);
            icon.row = (rows - 1 - icon.row) % rows;
            left   = (icon.column * SPRITE_SIZE) / width;
            right  = ((SPRITE_SIZE + icon.column * SPRITE_SIZE) - 0.01) / width;
            top    = ((SPRITE_SIZE + SPRITE_SIZE * icon.row) - 0.01) / height;
            bottom = (SPRITE_SIZE * icon.row) / height;
        }
        tileData.vertices = {
            // positions         // texture coords
            ratiodX,  0.5f, 0.0f,   right, top,      // top right
            ratiodX, -0.5f, 0.0f,   right, bottom,   // bottom right
            -ratiodX, -0.5f, 0.0f,  left, bottom,    // bottom left
            -ratiodX,  0.5f, 0.0f,  left, top        // top left
        };

        tileData.indices = {
            0, 1, 3,
            1, 2, 3
        };

        return tileData;
    }
	UI::UI(Texture texture, Icon icon, glm::vec2 ratio, glm::vec3 position, float zRotation, float scale, bool fullSize
		) :
		texture(std::move(texture)),
		ratio(ratio),
        fullSize(fullSize),
		position(position),
		zRotation(zRotation),
		scale(scale),
        shader(std::move(Shader("shaders/UIShader.vert", "shaders/UIShader.frag"))),
        mesh(std::move(Mesh(getUIVertices(icon, &texture, ratio, fullSize).vertices, getUIVertices(icon, &texture, ratio, fullSize).indices)))
	{
        relPos = glm::vec2(0, 0);
	}

	UI::~UI() {

	}

	void UI::draw(BaseGame* game) {
        auto drawPos = glm::vec3(position.x + relPos.x, position.y + relPos.y, position.z);
		auto mvpMatrix = game->calculateMvpMatrix(drawPos, zRotation, scale);
		shader.use();
		shader.setMatrix("uiMVP", mvpMatrix);
		texture.bind();
		mesh.draw();
	}

    void UI::moveUI(const glm::vec2& relativePosition) { 
        this->relPos = relativePosition; 
    }

    void UI::changeIcon(Icon newIcon) {
        mesh.updateMesh(getUIVertices(newIcon, &texture, ratio, fullSize).vertices);
    }
}