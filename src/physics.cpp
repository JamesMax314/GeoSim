#include "physics.hpp"

bool physics::RayIntersectsMesh(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
                       const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices,
                       glm::vec3& intersectionPoint) {
    for (size_t i = 0; i < indices.size(); i += 3) {
        const glm::vec3& vertex0 = vertices[indices[i]];
        const glm::vec3& vertex1 = vertices[indices[i + 1]];
        const glm::vec3& vertex2 = vertices[indices[i + 2]];

        if (RayIntersectsTriangle(rayOrigin, rayDirection, vertex0, vertex1, vertex2, intersectionPoint)) {
            return true;
        }
    }

    return false; // No intersection with any triangle in the mesh
}

bool physics::RayIntersectsTriangle(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
                           const glm::vec3& vertex0, const glm::vec3& vertex1, const glm::vec3& vertex2,
                           glm::vec3& intersectionPoint) {
    const float epsilon = 0.000001f;

    glm::vec3 edge1, edge2, h, s, q;
    float a, f, u, v;

    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = glm::cross(rayDirection, edge2);
    a = glm::dot(edge1, h);

    if (a > -epsilon && a < epsilon) {
        return false; // Ray is parallel to the triangle
    }

    f = 1.0f / a;
    s = rayOrigin - vertex0;
    u = f * glm::dot(s, h);

    if (u < 0.0f || u > 1.0f) {
        return false; // Intersection point is outside the triangle
    }

    q = glm::cross(s, edge1);
    v = f * glm::dot(rayDirection, q);

    if (v < 0.0f || u + v > 1.0f) {
        return false; // Intersection point is outside the triangle
    }

    float t = f * glm::dot(edge2, q);
    if (t > epsilon) {
        intersectionPoint = rayOrigin + t * rayDirection;
        return true; // Intersection found
    }

    return false; // Intersection point is behind the ray's origin
}