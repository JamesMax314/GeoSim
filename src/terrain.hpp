#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "extern/FastNoiseLite.hpp"

namespace terrain {
    class MeshGen {
        public:
        float sizeX;
        float sizeY;
        int numX;
        int numY;

        std::vector<glm::vec3> vertices;
        std::vector<unsigned int> indices;

        unsigned int vertSize;
        unsigned int indSize;

        std::vector<std::vector<float>> heightMap;

        void initPerlin();
        void initSimplex();
        void genMeshFromHeight(std::vector<std::vector<float>> heightMap);
        void genPerlinMesh();
        void simplex();

        MeshGen(float width, float height, int resWidth, int resHeight);
    };
}