#pragma once

#include <vector>

namespace ChunkMapEngine {
    /// Mesh represents OpenGL's vertex and element array buffer objects. 
    class Mesh {
    public:
        explicit Mesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);
        ~Mesh();

        Mesh(const Mesh& other) = default;

        Mesh(Mesh &&other) noexcept {
            std::swap(this->VBO, other.VBO);
            std::swap(this->EBO, other.EBO);
            std::swap(this->numberOfIndices, other.numberOfIndices);
            other.deleteBuffer = false;
        }

        /// draws the mesh to the screen.
        virtual void draw();
        /// updates the vertices in the vertex buffer. Allowing to change shape and texture coordinates.
        virtual void updateMesh(std::vector<float> vertices);

    protected:
        unsigned int VBO = 0;
        unsigned int EBO = 0;
        unsigned int numberOfIndices = 0;
        /// makes sure Buffers are not destroyed while still being used by a copy of the mesh.
        bool deleteBuffer = false;
    };
}

