#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <type_traits>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace shaders {
    std::string ReadShaderFile(const char* filePath);

    GLuint genShaderProgram(const char* vertexShader, const char* fragmentShader);

    class ShaderManager {
        public:
        std::vector<unsigned int> shaderIndices;
        std::vector<GLuint> shaderList;
        GLuint activeShader;

        unsigned int addShader(const char* vertexShader, const char* fragmentShader);

        GLuint activateShader(unsigned int shaderInd);
        void close();

        ShaderManager();

        unsigned int activeShaderInd;
    };

    class Shader {
        public:
        GLuint program;

        Shader();
        Shader(const char* vertexShader, const char* fragmentShader);

    };


    template <typename dataType>
    void setUniformVec(GLuint shaderProgram, const char *name, dataType &data)
    {
        GLuint location = glGetUniformLocation(shaderProgram, name);

        // todo seperate into if blocks
        if (typeid(dataType) == typeid(glm::mat4)) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
        } else if (typeid(dataType) == typeid(glm::vec3)) {
            glUniform3fv(location, 1, glm::value_ptr(data));
        }   
    }

    template <typename dataType>
    void setUniform(GLuint shaderProgram, const char *name, dataType &data)
    {
        GLuint location = glGetUniformLocation(shaderProgram, name);

        if (typeid(dataType) == typeid(float)) {
            glUniform1f(location, data);
        } else if (typeid(dataType) == typeid(int)) {
            glUniform1i(location, data);
        }   
    }
}
