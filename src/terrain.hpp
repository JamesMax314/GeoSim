#include <vector>

#include "extern/FastNoiseLite.hpp"

namespace terrain {
    class MeshGen {
        public:
        float sizeX;
        float sizeY;
        int numX;
        int numY;

        float* vertices;
        unsigned int* indices;

        unsigned int vertSize;
        unsigned int indSize;

        std::vector<std::vector<float>> heightMap;

        void initPerlin();
        void genMeshFromHeight(std::vector<std::vector<float>> heightMap);
        void genPerlinMesh();

        MeshGen(float width, float height, int resWidth, int resHeight);
    };
}