#include "camera.hpp"
#include <iostream>

void camera::Camera::move(float x, float y, float z)
{
    camPos.x = x;
    camPos.y = y;
    camPos.z = z;
    viewMatrix = glm::translate(viewMatrix, camPos);
}

camera::Camera::Camera()
{
    // Set camera to origin
    camPos = glm::vec3(0.0f, 0.0f, 0.0f);
    motionSpeed = 10.0f;
    // viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

}
