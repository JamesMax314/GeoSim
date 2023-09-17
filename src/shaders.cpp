#include "shaders.hpp"

std::string shaders::ReadShaderFile(const char* filePath) {
    std::string shaderCode;
    std::ifstream shaderFile;

    // Ensure ifstream objects can throw exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open the file
        shaderFile.open(filePath);
        std::stringstream shaderStream;

        // Read the file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();

        // Close the file
        shaderFile.close();

        // Convert the stream into a string
        shaderCode = shaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cerr << "Error reading shader file: " << e.what() << std::endl;
    }
    // printf(shaderCode.c_str());
    return shaderCode;
}

GLuint shaders::genShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile) {
    std::string vertexShaderSource = shaders::ReadShaderFile(vertexShaderFile);
    std::string fragmentShaderSource = shaders::ReadShaderFile(fragmentShaderFile);

    const char* vertex = vertexShaderSource.c_str();
    const char* fragment = fragmentShaderSource.c_str();

    // Create and compile the shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create a shader program and link the shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(shaderProgram);

    printf("Shader Compiled\n");

    return shaderProgram;
}

unsigned int shaders::ShaderManager::addShader(const char *vertexShader, const char *fragmentShader)
{
    shaderList.emplace_back(shaders::genShaderProgram(vertexShader, fragmentShader));
    return shaderList.size() - 1;
}

GLuint shaders::ShaderManager::activateShader(unsigned int shaderInd)
{
    GLuint shaderProgram = shaderList[shaderInd];
    if (shaderInd != activeShader) {
        glUseProgram(shaderProgram);
    }
    return shaderProgram;
}

void shaders::ShaderManager::close()
{
    for (int i=0; i<shaderList.size(); i++) {
        glDeleteProgram(shaderList[i]);
    }
}

shaders::ShaderManager::ShaderManager()
{
}
