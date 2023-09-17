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
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
    };

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
        glm::mat3 normalModel;
        glm::vec3 fogColor;
        glm::vec3 lightColor;
        glm::vec3 lightPos;
        float rockScale;
        float fogDensity;
        std::vector<glm::vec3> mVertices;
        std::vector<glm::vec3> normals;
        std::vector<Vertex> interleafed;
        std::vector<unsigned int> mIndices;


        // Intagers that are used to reference buffer arrays in gpu ram
        GLuint VAO;
        GLuint VBO; // Vertices
        GLuint EBO; // Indices
        GLuint NBO; // Normals



        shaders::ShaderManager mShaderManager;
    };


    std::vector<Vertex> interleafVertices(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals);
    std::vector<glm::vec3> computeNormals(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);


}