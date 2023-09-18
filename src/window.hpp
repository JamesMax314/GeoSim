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
#include "camera.hpp"
#include "light.hpp"
#include "shaders.hpp"

namespace window {
    GLFWwindow* setupWindow();
    void setFullScreen(GLFWwindow* window);
    void setSmallScreen(GLFWwindow* window);

    class Window : public shaders::ShaderManager {
        public:

        GLFWwindow* win;

        int lightingMode;

        camera::Camera* cam;
        std::vector<light::Light*> lights;
        std::vector<drawable::GroundMesh*> meshes;

        Window();
        void setFullScreen();
        void setSmallScreen();

        void renderFrame();

        void addLight(light::Light *mLight);
        void addMesh(drawable::GroundMesh *mesh);
        void setCamera(camera::Camera *mCam);

        GLFWwindow* getContext();
    };
}