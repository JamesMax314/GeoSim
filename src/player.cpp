#include "player.hpp"

void player::Player::move(float x, float y, float z)
{
    if (not flying) {
        // playerVel = {0.0f, 0.0f, 0.0f};
        if (y > 0.0f && grounded) {
            playerVel = {0.0f, 10.0f, 0.0f};
            grounded = false;
        }
        y = 0.0f;
    }

    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 playerFrontNoUp = glm::vec3(playerFacing[0], 0.0f, playerFacing[2]); // Allows motion only in the plain 

    playerPos += -x*glm::cross(playerFrontNoUp, worldUp) + y*worldUp + z*playerFrontNoUp;
}

void player::Player::rotate(float dx, float dy)
{
    float angX = -dx*rotSpeed;
    float angY = -dy*rotSpeed;

    glm::mat4 yawRotation = glm::rotate(glm::mat4(1.0f), angX, up);
    playerFacing = glm::vec3(yawRotation * glm::vec4(playerFacing, 0.0f));

    // Pitch (up/down rotation)
    glm::mat4 pitchRotation = glm::rotate(glm::mat4(1.0f), angY, glm::cross(playerFacing, up));
    playerFacing = glm::vec3(pitchRotation * glm::vec4(playerFacing, 0.0f));
}

glm::mat4 player::Player::getCamPos()
{
    glm::vec3 cameraTarget = playerPos + playerFacing;
    glm::mat4 viewMatrix = glm::lookAt(playerPos, cameraTarget, up);
    return viewMatrix;
}

bool player::Player::checkGrounded()
{
    glm::vec3 intersectionPoint;
    bool foundIntersect = physics::RayIntersectsMesh(playerPos, down, mGround.mVertices, mGround.mIndices, intersectionPoint);
    return foundIntersect;
}

void player::Player::resolveGroundCollision()
{
    glm::vec3 intersectionPoint;
    bool foundIntersect = physics::RayIntersectsMesh(playerPos, down, mGround.mVertices, mGround.mIndices, intersectionPoint);
    // printf("intersect: [%f, %f, %f] \n", intersectionPoint[0], intersectionPoint[1], intersectionPoint[2]);

    if (foundIntersect) {
        if (glm::length(playerPos - intersectionPoint) < playerHeight) {
            playerPos[1] = intersectionPoint[1] + playerHeight;
            grounded = true;
        }
    }
}

void player::Player::toggleFly()
{
    flying = not flying;
}

void player::Player::physicsUpdate(float dt)
{
    if (not flying) {
        playerPos += dt*playerVel;
        if (not grounded) {
            playerVel += dt*gravity;
        }
    }
    resolveGroundCollision();
}

player::Player::Player(drawable::GroundMesh& ground, float camHeight)
{
    flying = true;
    grounded = false;
    mGround = ground;
    playerHeight = camHeight;
    down = {0.0f, -1.0f, 0.0f};
    up = -down;

    gravity = {0.0f, -10.0f, 0.0f};
    playerVel = {0.0f, 0.0f, 0.0f};
    playerPos = {0.0f, 0.0f, 3.0f};
    playerFacing = {0.0f, 0.0f, -1.0f};
    motionSpeed = 10.0f;
    rotSpeed = 0.005f;
}