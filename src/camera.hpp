#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace camera {
    class Camera {
        public:
        glm::mat4 viewMatrix;
        glm::vec3 camPos;

        float motionSpeed;

        void move(float x, float y, float z);

        Camera();
    };
}