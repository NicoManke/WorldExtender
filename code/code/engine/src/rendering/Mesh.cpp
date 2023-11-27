#include "engine/rendering/Mesh.h"
#include "glad/glad.h"
#include "engine/Logger.h"
#include <iostream>

namespace ChunkMapEngine {
    template<typename T>
    GLuint createBuffer(GLuint bufferType, const std::vector<T> &bufferData) {
        unsigned int buffer = 0;
        glGenBuffers(1, &buffer);
        glBindBuffer(bufferType, buffer);
        glBufferData(bufferType, bufferData.size() * sizeof(T), bufferData.data(), GL_STATIC_DRAW);
        return buffer;
    }

    Mesh::Mesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices):
            numberOfIndices(indices.size()),
            VBO(createBuffer(GL_ARRAY_BUFFER, vertices)),
            EBO(createBuffer(GL_ELEMENT_ARRAY_BUFFER, indices)){
    }

    void Mesh::draw() {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, nullptr);
    }
    
    void Mesh::updateMesh(std::vector<float> newData) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
        GLintptr offset = 0; 
        GLsizeiptr size = 20 * sizeof(float); 
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, newData.data());
    
        // Unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Mesh::~Mesh() {
        if (deleteBuffer) {
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }
    }
}
