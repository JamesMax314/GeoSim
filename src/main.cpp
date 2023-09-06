#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "extern/FastNoiseLite.hpp"

#include "window.hpp"
#include "camera.hpp"
#include "terrain.hpp"
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

unsigned int indices3[] = {
    7, 4, 0,
    0, 0, 0,
    6, 5, 1,
    0, 0, 0,
    6, 7, 3,
    0, 0, 0,
    5, 4, 0,
    0, 0, 0,
    2, 3, 0,
    0, 0, 0,
    6, 7, 4,
    0, 0, 0,
};

unsigned int indices2[] = {
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4,
    0, 3, 7,
    7, 4, 0,
    1, 2, 6,
};

double deltaTime;
camera::Camera cam;

bool keys[GLFW_KEY_LAST] = { false };
bool fullScreen = false;

double prevMouseX = 0.0;
double prevMouseY = 0.0;
double deltaX;
double deltaY;

// Mouse cursor position callback function
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    // Calculate the change in mouse cursor position
    deltaX = xpos - prevMouseX;
    deltaY = ypos - prevMouseY;

    // Update the previous mouse cursor position
    prevMouseX = xpos;
    prevMouseY = ypos;

    // Use deltaX and deltaY to respond to mouse movement
    // Your code here
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keys[key] = true; // Set the key state to true when pressed

        if (key == GLFW_KEY_F) {
            if (fullScreen) {
                window::setSmallScreen(window);
                fullScreen = false;
            } else {
                window::setFullScreen(window);
                fullScreen = true;
            }
        }

    } else if (action == GLFW_RELEASE) {
        keys[key] = false; // Set the key state to false when released
    }

    

    if (key == GLFW_KEY_ESCAPE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetWindowShouldClose(window, GLFW_TRUE); // Close the window when ESC is pressed
    }
}

int main() {

    GLFWwindow* window = window::setupWindow();

    const char* vertexShaderFile = "../src/shaders/3d_vert.glsl";
    const char* fragmentShaderFile = "../src/shaders/3d_frag.glsl";
    const char* rocks_fragmentShaderFile = "../src/shaders/colourHills_frag.glsl";


    shaders::ShaderManager shaderMan = shaders::ShaderManager();
    shaderMan.addShader(vertexShaderFile, fragmentShaderFile);
    shaderMan.addShader(vertexShaderFile, rocks_fragmentShaderFile);


    cam = camera::Camera();

    terrain::MeshGen perlinMesh(400, 400, 2000, 2000);
    perlinMesh.genPerlinMesh();

    // drawable::ThreeDimMesh testD = drawable::ThreeDimMesh(shaderMan, 1, vertices, indices3, sizeof(vertices)/sizeof(float), sizeof(indices)/sizeof(float));
    drawable::ThreeDimMesh meshDraw = drawable::ThreeDimMesh(shaderMan, 1, perlinMesh.vertices, perlinMesh.indices, perlinMesh.vertSize, perlinMesh.indSize);


    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    double previousFrameTime = glfwGetTime();
    double currentFrameTime;

    // Keyboard input callback
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Gray color with RGB values of 0.5 (50% gray)

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - previousFrameTime;
        // std::cout << '\r' << "                         " << std::flush;
        // std::cout << '\r' << "FPS: " << 1/deltaTime << std::flush;

        if (keys[GLFW_KEY_W]) {
            cam.move(0.0f, 0.0f, cam.motionSpeed*deltaTime);
        }
        if (keys[GLFW_KEY_S]) {
            cam.move(0.0f, 0.0f, -cam.motionSpeed*deltaTime);
        }
        if (keys[GLFW_KEY_A]) {
            cam.move(cam.motionSpeed*deltaTime, 0.0f, 0.0f);
        }
        if (keys[GLFW_KEY_D]) {
            cam.move(-cam.motionSpeed*deltaTime, 0.0f, 0.0f);
        }
        if (keys[GLFW_KEY_SPACE]) {
            cam.move(0.0f, -cam.motionSpeed*deltaTime, 0.0f);
        }
        if (keys[GLFW_KEY_LEFT_SHIFT]) {
            cam.move(0.0f, cam.motionSpeed*deltaTime, 0.0f);
        }

        if (deltaX != 0.0 || deltaY != 0.0) {
            cam.rotate(deltaX, deltaY);
            deltaX = 0;
            deltaY = 0;
        }

        // testD.updatePerspective(cam.viewMatrix);
        // testD.draw(window, cam);

        meshDraw.draw(window, cam);
        // testD.draw(window, cam);


        // Update the previous frame time for the next frame
        previousFrameTime = currentFrameTime;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup

    glfwTerminate();
    return 0;
}

// TODO: add an object class that contains a drawable and a collision mesh
// TODO: make drawable able to use different shaders with different parameters, i.e. have a list of parameters and names that can be passed. may need a try catch to handle the types
// TODO: wite a collision detector that takes a vertex array and checks for intersection between adjacent vertices. resolve gravity and cancle frictino to find the force on the player
// Will need a material class and a world class with gravity etc...
// TODO: rename window namespace