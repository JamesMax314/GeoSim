#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace shaders {
    std::string ReadShaderFile(const char* filePath);

    GLuint genShaderProgram(const char* vertexShader, const char* fragmentShader);

    class ShaderManager {
        public:
        std::vector<unsigned int> shaderIndices;
        std::vector<GLuint> shaderList;

        unsigned int addShader(const char* vertexShader, const char* fragmentShader);

        GLuint activateShader(unsigned int shaderInd);
        void close();

        ShaderManager();

        private:
        unsigned int activeShader;
    };
}

