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
    typedef glm::vec3 Vertex;

    struct VertexNormal {
        glm::vec3 position;
        glm::vec3 normal;
    };

    struct VertexNormalText {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 texture;
    };

    class Drawable {
        public:
        unsigned int shaderProgramIndex;

        std::vector<glm::vec3> mVertices;
        std::vector<unsigned int> mIndices;

        // Intagers that are used to reference buffer arrays in gpu ram
        GLuint VAO;
        GLuint VBO; // Vertices
        GLuint EBO; // Indices
        GLuint NBO; // Normals
        glm::mat4 model;
        glm::mat3 normalModel;

        Drawable();
        void fillBuffers();
        void loadUniforms(GLuint shader);
        void draw(GLFWwindow* w);
    };

    class GroundMesh : public Drawable {
        public:
        void updatePerspective(glm::mat4 viewMatrix);
        void fillBuffers(GLFWwindow* w);
        void loadUniforms(GLuint shader);

        GroundMesh();
        GroundMesh(unsigned int shaderInd, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
        ~GroundMesh();

        int lightingMode;
        glm::mat4 projection;
        glm::mat4 view;
        glm::mat3 normalModel;

        float lightingModerockScale;
        float rockScale;

        // Object meshes require normlas for lighting
        std::vector<glm::vec3> normals;
        std::vector<VertexNormal> interleafed;

        shaders::ShaderManager mShaderManager;
    };


    std::vector<VertexNormal> interleafVertices(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals);
    std::vector<glm::vec3> computeNormals(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);


}