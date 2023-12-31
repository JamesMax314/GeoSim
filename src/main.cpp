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
#include "player.hpp"


double deltaTime;
camera::Camera cam;

bool keys[GLFW_KEY_LAST] = { false };
bool fullScreen = false;
bool toggleFlight = false;

int lightingMode = 2;
int colourMode = 0;

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

        if (key == GLFW_KEY_L) {
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

        if (key == GLFW_KEY_F) {
            toggleFlight = true;
        }

        if (key == GLFW_KEY_O) {
            lightingMode += 1;
            lightingMode = lightingMode%3;
        }

        if (key == GLFW_KEY_P) {
            colourMode += 1;
            colourMode = colourMode%2;
        }
    }

    if (key == GLFW_KEY_ESCAPE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetWindowShouldClose(window, GLFW_TRUE); // Close the window when ESC is pressed
    }
}

int main() {

    // GLFWwindow* window = window::setupWindow();
    window::Window mWindow = window::Window();
    // GLFWwindow* contextWindow = mWindow.getContext();


    const char* vertexShaderFile = "../src/shaders/3d_vert.glsl";
    const char* fragmentShaderFile = "../src/shaders/3d_frag.glsl";
    const char* rocks_fragmentShaderFile = "../src/shaders/colourHills_frag.glsl";
    const char* phongFrag = "../src/shaders/phong.glsl";

    // shaders::ShaderManager shaderMan = shaders::ShaderManager();
    mWindow.addShader(vertexShaderFile, fragmentShaderFile);
    mWindow.addShader(vertexShaderFile, rocks_fragmentShaderFile);
    mWindow.addShader(vertexShaderFile, phongFrag);

    shaders::Shader terrainShader(vertexShaderFile, phongFrag);

    cam = camera::Camera();

    terrain::MeshGen perlinMesh(40, 40, 200, 200);
    perlinMesh.genPerlinMesh();

    // drawable::ThreeDimMesh testD = drawable::ThreeDimMesh(shaderMan, 1, vertices, indices3, sizeof(vertices)/sizeof(float), sizeof(indices)/sizeof(float));
    drawable::GroundMesh meshDraw = drawable::GroundMesh(2, perlinMesh.vertices, perlinMesh.indices);
    light::Light mLight = light::Light();
    mWindow.addLight(&mLight);
    mWindow.addMesh(&meshDraw);
    mWindow.setCamera(&cam);

    player::Player play(meshDraw, 0.5);


    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    double previousFrameTime = glfwGetTime();
    double currentFrameTime;

    // Keyboard input callback
    glfwSetKeyCallback(mWindow.getContext(), keyCallback);
    glfwSetCursorPosCallback(mWindow.getContext(), cursorPosCallback);
    glfwSetInputMode(mWindow.getContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Gray color with RGB values of 0.5 (50% gray)

    double printFPSTime = 0.5;
    double deltaFPSTime = 0;

    // Main rendering loop
    while (!glfwWindowShouldClose(mWindow.getContext())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - previousFrameTime;
        deltaFPSTime += deltaTime;
        if (deltaFPSTime > printFPSTime) {
            std::cout << '\r' << "                         " << std::flush;
            std::cout << '\r' << "FPS: " << 1/deltaTime << std::flush;
            deltaFPSTime = 0;
        }

        if (toggleFlight) {
            play.toggleFly();
            toggleFlight = false;
        }

        if (keys[GLFW_KEY_W]) {
            play.move(0.0f, 0.0f, play.motionSpeed*deltaTime);
        }
        if (keys[GLFW_KEY_S]) {
            play.move(0.0f, 0.0f, -play.motionSpeed*deltaTime);
        }
        if (keys[GLFW_KEY_A]) {
            play.move(play.motionSpeed*deltaTime, 0.0f, 0.0f);
        }
        if (keys[GLFW_KEY_D]) {
            play.move(-play.motionSpeed*deltaTime, 0.0f, 0.0f);
        }
        if (keys[GLFW_KEY_SPACE]) {
            play.move(0.0f, play.motionSpeed*deltaTime, 0.0f);
        }
        if (keys[GLFW_KEY_LEFT_SHIFT]) {
            play.move(0.0f, -play.motionSpeed*deltaTime, 0.0f);
        }

        if (deltaX != 0.0 || deltaY != 0.0) {
            play.rotate(deltaX, deltaY);
            deltaX = 0;
            deltaY = 0;
        }
        
        play.physicsUpdate(deltaTime);

        cam.setViewMat(play.getCamPos());
        cam.camPos = play.playerPos;

        // testD.updatePerspective(cam.viewMatrix);
        // testD.draw(window, cam);
        mWindow.lightingMode = lightingMode;
        mWindow.colourMode = colourMode;

        mWindow.renderFrame();

        // Update the previous frame time for the next frame
        previousFrameTime = currentFrameTime;

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
// TODO: camera needs a method to take players location and direction data