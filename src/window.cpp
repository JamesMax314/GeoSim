#include "window.hpp"

GLFWwindow* window::setupWindow() {
        // Initialize GLFW and create a window
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    // Necessary to use glsl 330 standard
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    // std::cout << "I'm apple machine" << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL 3D Cube", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
    }

    return window;
}

void window::setFullScreen(GLFWwindow* window)
{
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

    // Get the video mode of the primary monitor
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    // Switch to fullscreen mode
    glfwSetWindowMonitor(window, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

void window::setSmallScreen(GLFWwindow *window)
{
    glfwSetWindowMonitor(window, NULL, 100, 100, 800, 600, GLFW_DONT_CARE);
}

window::Window::Window()
{
    win = setupWindow();
}

void window::Window::renderFrame()
{
    // To allow rendering to the visible screen, we need the set the context
    glfwMakeContextCurrent(win);

    // Todo: loop over lights and pass locations and positions to frag shader (need uniform buffer)

    // Activate the appropriate shader program
    activateShader(meshes[0]->shaderProgramIndex);

    // Get uniform locations for additional parameters
    // Standard uniforms
    shaders::setUniformVec(activeShader, "view", cam->viewMatrix);
    shaders::setUniformVec(activeShader, "viewPos", cam->camPos);
    shaders::setUniformVec(activeShader, "lightColour", lights[0]->lightColor);
    shaders::setUniformVec(activeShader, "lightLocation", lights[0]->lightPos);
    shaders::setUniform(activeShader, "lightingMode", lightingMode);
    
    // Model specific uniforms
    meshes[0]->loadUniforms(activeShader);
    meshes[0]->fillBuffers(win);
    meshes[0]->draw(win);
    // printf("camPos: [%f, %f, %f] \n", cam->camPos[0], cam->camPos[1], cam->camPos[2]);

    glfwSwapBuffers(win);
}

void window::Window::setFullScreen()
{
    window::setFullScreen(win);
}

void window::Window::setSmallScreen()
{
    window::setSmallScreen(win);
}

void window::Window::addLight(light::Light *mLight)
{
    lights.emplace_back(mLight);
}

void window::Window::addMesh(drawable::GroundMesh *mesh)
{
    meshes.emplace_back(mesh);
}

void window::Window::setCamera(camera::Camera *mCam)
{
    cam = mCam;
}

GLFWwindow *window::Window::getContext()
{
    return win;
}
