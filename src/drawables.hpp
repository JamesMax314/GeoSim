#pragma once

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders.hpp"
#include "camera.hpp"

namespace drawable {
    class Drawable {
        public:
        unsigned int shaderProgramIndex;
        virtual void update();
        virtual void draw(GLFWwindow* window, camera::Camera cam);

        Drawable();
    };

    class ThreeDimMesh : public Drawable {
        public:
        void update() override;
        void draw(GLFWwindow* window, camera::Camera cam) override;
        void updatePerspective(glm::mat4 viewMatrix);

        ThreeDimMesh();
        ThreeDimMesh(shaders::ShaderManager &shaderManager, unsigned int shaderInd, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
        ~ThreeDimMesh();
        

        glm::mat4 projection;
        glm::mat4 view;
        glm::mat4 model;
        glm::vec3 fogColor;
        float rockScale;
        float fogDensity;
        std::vector<glm::vec3> mVertices;
        std::vector<unsigned int> mIndices;

        GLuint VAO;
        GLuint VBO;
        GLuint EBO;


        shaders::ShaderManager mShaderManager;
    };
}