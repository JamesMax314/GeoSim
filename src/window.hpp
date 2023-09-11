#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace window {
    GLFWwindow* setupWindow();
    void setFullScreen(GLFWwindow* window);
    void setSmallScreen(GLFWwindow* window);
}