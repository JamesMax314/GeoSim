#include "terrain.hpp"

terrain::MeshGen::MeshGen(float width, float height, int resWidth, int resHeight)
{
    sizeX = width;
    sizeY = height;
    numX = resWidth;
    numY = resHeight;
}

void terrain::MeshGen::initPerlin()
{
    // Create a FastNoise object for Perlin noise generation
    FastNoiseLite myNoise;
    
    // Set the seed for deterministic noise
    myNoise.SetSeed(12345);

    // Create a 2D vector to store the Perlin noise values
    heightMap = std::vector<std::vector<float>>(numX, std::vector<float>(numY));

    // Generate Perlin noise values for each point in the 2D grid
    for (int x = 0; x < numX; x++) {
        for (int y = 0; y < numY; y++) {
            // Generate the Perlin noise value for the current (x, y) point
            float noiseValue = myNoise.GetNoise(static_cast<float>(x), static_cast<float>(y));

            // Store the noise value in the 2D array
            heightMap[x][y] = noiseValue;
        }
    }
    printf("Noise Generated \n");
}

void terrain::MeshGen::genMeshFromHeight(std::vector<std::vector<float>> heightMap)
{
    float minX = -sizeX/2;
    float maxX = sizeX/2;
    float stepX = sizeX/numX;
    float minY = -sizeX/2;
    float maxY = sizeX/2;
    float stepY = sizeY/numY;

    vertSize = numX*numY*3;
    printf("vertSize %u \n", vertSize);
    indSize = (numX-1)*(numY-1)*3*2; // 3 verts per triangle, 2 triangles per square
    vertices = new float[vertSize];
    indices = new unsigned int[indSize];

    for (int i=0; i<numX; i++) {
        for (int j=0; j<numY; j++) {
            vertices[j*3 + i*3*numY + 0] = minX+i*stepX;
            vertices[j*3 + i*3*numY + 1] = heightMap[i][j];
            vertices[j*3 + i*3*numY + 2] = minY+j*stepY;
        }
    }

    // for (int i=0; i<vertSize/3; i++) {
    //     printf(" %f, %f, %f \n", vertices[i*3], vertices[i*3+1], vertices[i*3+2]);
    // }

    for (unsigned int i=0; i<numX-1; i++) {
        for (unsigned int j=0; j<numY-1; j++) {
            indices[j*3 + i*3*numY+0] = j;
            indices[j*3 + i*3*numY+1] = j+1;
            indices[j*3 + i*3*numY+2] = (i+1)*numY+j;

            // printf("index: %u %u \n", j + i*numY+2, indices[j + i*numY+2]);

            indices[j*3 + i*3*numY+3 + (numX-1)*(numY-1)] = numY*numX - j;
            indices[j*3 + i*3*numY+4 + (numX-1)*(numY-1)] = numY*numX - (j+1);
            indices[j*3 + i*3*numY+5 + (numX-1)*(numY-1)] = numY*numX - ((i+1)*numY+j);
        }
    }
    
    // for (int i=0; i<indSize/6; i++) {
    //     printf(" %u, %u, %u \n", indices[i*6], indices[i*6+1], indices[i*6+2]);
    //     printf(" %u, %u, %u \n", indices[i*6+3], indices[i*6+4], indices[i*6+5]);
    // }
}

void terrain::MeshGen::genPerlinMesh()
{
    initPerlin();
    genMeshFromHeight(heightMap);
}
