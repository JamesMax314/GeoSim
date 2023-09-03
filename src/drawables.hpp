#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders.hpp"

namespace drawable {
    class Drawable {
        public:
        unsigned int shaderProgramIndex;
        virtual void update();
        virtual void draw(GLFWwindow* window);

        Drawable();
    };

    class ThreeDimMesh : public Drawable {
        public:
        void update() override;
        void draw(GLFWwindow* window) override;
        void updatePerspective(glm::mat4 viewMatrix);

        ThreeDimMesh();
        ThreeDimMesh(shaders::ShaderManager &shaderManager, unsigned int shaderInd, float* vertices, unsigned int* indices, int numVerts, int numInds);
        ~ThreeDimMesh();
        

        glm::mat4 projection;
        glm::mat4 view;
        glm::mat4 model;
        glm::vec3 fogColor;
        float fogDensity;
        float* mVertices;
        unsigned int* mIndices;
        int vertSize;
        int indSize;

        GLuint VAO;
        GLuint VBO;
        GLuint EBO;


        shaders::ShaderManager mShaderManager;
    };
}