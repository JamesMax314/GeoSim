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
    FastNoiseLite lowFrew;
    FastNoiseLite highFreq;
    FastNoiseLite highFreq2;


    lowFrew.SetFrequency(0.1f);
    highFreq.SetFrequency(1.0f);
    highFreq2.SetFrequency(5.0f);


    lowFrew.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    highFreq.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    highFreq2.SetNoiseType(FastNoiseLite::NoiseType_Perlin);


    
    // Set the seed for deterministic noise
    lowFrew.SetSeed(12345);
    highFreq.SetSeed(54321);
    highFreq2.SetSeed(21);

    float stepX = sizeX / numX;
    float stepY = sizeY / numY;

    float minX = -sizeX/2;
    float minY = -sizeY/2;

    // Create a 2D vector to store the Perlin noise values
    heightMap = std::vector<std::vector<float>>(numX, std::vector<float>(numY));

    // Generate Perlin noise values for each point in the 2D grid
    for (int x = 0; x < numX; x++) {
        for (int y = 0; y < numY; y++) {
            // Generate the Perlin noise value for the current (x, y) point
            float noiseValue = lowFrew.GetNoise(x*stepX+minX, y*stepY+minY)*2;
            noiseValue += highFreq.GetNoise(x*stepX+minX, y*stepY+minY)*0.05;
            noiseValue += highFreq2.GetNoise(x*stepX+minX, y*stepY+minY)*0.01;


            // Store the noise value in the 2D array
            heightMap[x][y] = noiseValue;
        }
    }
    // printf("Noise Generated \n");
}

void terrain::MeshGen::initSimplex()
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
}

void terrain::MeshGen::genMeshFromHeight(std::vector<std::vector<float>> heightMap)
{
    float minX = -sizeX/2;
    float maxX = sizeX/2;
    float stepX = sizeX/(numX-1);
    float minY = -sizeX/2;
    float maxY = sizeX/2;
    float stepY = sizeY/(numY-1);

    vertSize = numX*numY*3;
    indSize = (numX-1)*(numY-1)*3*2; // 3 verts per triangle, 2 triangles per square 78 54
    vertices = {};
    indices = {};

    for (int i=0; i<numX; i++) {
        for (int j=0; j<numY; j++) {
            glm::vec3 vertex(minX+i*stepX, heightMap[i][j]*4, minY+j*stepY);
            vertices.emplace_back(vertex);
        }
    }

    // for (int i=0; i<vertSize/3; i++) {
        // printf(" %f, %f, %f \n", vertices[i*3], vertices[i*3+1], vertices[i*3+2]);
    // }

    // The last vertex in each dimension is included by the j+1 etc so we iterate up to N-1
    for (unsigned int i=0; i<numX-1; i++) {
        for (unsigned int j=0; j<numY-1; j++) {
            indices.emplace_back(i*numY + j);
            indices.emplace_back(i*numY + j+1);
            indices.emplace_back((i+1)*numY+j);

            // printf("index: %u %u \n", j + i*numY+2, indices[j + i*numY+2]);

            indices.emplace_back(numY*numX - (i*numY + j) - 1);
            indices.emplace_back(numY*numX - (i*numY + j+1) - 1);
            indices.emplace_back(numY*numX - ((i+1)*numY+j) - 1);

        }
    }

    // printf("proper size: %u \n", indSize);
    // printf("indices Size: %u \n", (numY-2)*6 + (numX-2)*6*(numY-1)+5 + 1);

    // printf(" %u, %u, %u \n", indices[0], indices[1], indices[2]);
    // printf(" %u, %u, %u \n", indices[3], indices[4], indices[5]);

    // for (int i=0; i<indSize/6; i++) {
        // printf(" %u, %u, %u \n", indices[i*6], indices[i*6+1], indices[i*6+2]);
        // printf(" %u, %u, %u \n", indices[i*6+3], indices[i*6+4], indices[i*6+5]);
    // }

    // printf("ind: %u \n", indices[indSize]);
}

void terrain::MeshGen::genPerlinMesh()
{
    initPerlin();
    genMeshFromHeight(heightMap);
}

void terrain::MeshGen::simplex()
{

}
