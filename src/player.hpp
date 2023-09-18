#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "drawables.hpp"
#include "physics.hpp"

namespace player
{
    class Player {
        public:
        bool flying;
        bool grounded;

        float playerHeight;
        float rotSpeed;
        float motionSpeed;

        glm::vec3 gravity;
        glm::vec3 playerVel;
        glm::vec3 playerPos;
        glm::vec3 playerFacing;
        glm::vec3 down;
        glm::vec3 up;

        drawable::GroundMesh mGround;

        void move(float x, float y, float z);
        void rotate(float dx, float dy);

        glm::mat4 getCamPos();

        
        bool checkGrounded();
        void resolveGroundCollision();
        void toggleFly();
        void physicsUpdate(float dt);
        Player(drawable::GroundMesh &ground, float camHeight);
    };
}