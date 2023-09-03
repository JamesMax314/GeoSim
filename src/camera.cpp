#include "camera.hpp"

void camera::Camera::move(float x, float y, float z)
{
    camPos.x += x;
    camPos.y += y;
    camPos.z += z;
    viewMatrix = glm::translate(viewMatrix, -camPos);
}

camera::Camera::Camera()
{
    // Set camera to origin
    camPos = glm::vec3(0.0f, 0.0f, 0.0f);
    viewMatrix = glm::mat4(1.0f);
}
