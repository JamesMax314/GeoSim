#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.hpp"
#include "camera.hpp"
#include "shaders.hpp"
#include "drawables.hpp"

// Vertex data for a 3D cube
float vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    // Back face
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4,
    0, 3, 7,
    7, 4, 0,
    1, 2, 6,
    6, 5, 1,
    3, 2, 6,
    6, 7, 3,
    0, 1, 5,
    5, 4, 0,
};

double deltaTime;
camera::Camera cam;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        // Key was pressed
        if (key == GLFW_KEY_W) {
            cam.move(0.0f, 0.0f, cam.motionSpeed*deltaTime); // Close the window when ESC is pressed
        }
    }
}

int main() {

    GLFWwindow* window = window::setupWindow();

    const char* vertexShaderFile = "../src/shaders/3d_vert.glsl";
    const char* fragmentShaderFile = "../src/shaders/3d_frag.glsl";

    shaders::ShaderManager shaderMan = shaders::ShaderManager();
    shaderMan.addShader(vertexShaderFile, fragmentShaderFile);

    cam = camera::Camera();

    drawable::ThreeDimMesh testD = drawable::ThreeDimMesh(shaderMan, 0, vertices, indices);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    double previousFrameTime = glfwGetTime();
    double currentFrameTime;

    // Keyboard input callback
    glfwSetKeyCallback(window, keyCallback);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - previousFrameTime;

        // Update model matrix (rotation)
        // model = glm::rotate(model, (float)glfwGetTime()/1000, glm::vec3(1.0f, 0.5f, 0.2f));
        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // testD.updatePerspective(cam.viewMatrix);
        testD.draw(window);

        // Update the previous frame time for the next frame
        previousFrameTime = currentFrameTime;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup

    glfwTerminate();
    return 0;
}
