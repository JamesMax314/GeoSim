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

#include "drawables.hpp"

namespace light {

    class Light : public drawable::Drawable{
        public:

        glm::vec3 lightColor;
        glm::vec3 lightPos;

        Light();
        
    };
}