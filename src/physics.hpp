#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace physics
{
    bool RayIntersectsMesh(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
                        const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices,
                        glm::vec3& intersectionPoint);
    
    bool RayIntersectsTriangle(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
                           const glm::vec3& vertex0, const glm::vec3& vertex1, const glm::vec3& vertex2,
                           glm::vec3& intersectionPoint);
}