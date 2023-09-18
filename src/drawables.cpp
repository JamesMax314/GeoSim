#include "drawables.hpp"

drawable::Drawable::Drawable()
{
}

void drawable::Drawable::fillBuffers()
{
    // Bind all the model arrays to the appropriate buffers
    glBindVertexArray(VAO);

    // Vertex buffer contains vertices and indices interleafed
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), &mVertices.front(), GL_STATIC_DRAW);

    // Tell the shader how the interleafing should be undone
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Index buffer contains just the indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size()*sizeof(unsigned int), &mIndices.front(), GL_STATIC_DRAW);
}

void drawable::Drawable::loadUniforms(GLuint shader)
{

}

void drawable::Drawable::draw(GLFWwindow* w)
{
    glfwMakeContextCurrent(w);
    // Bind model buffers and draw to screen
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
}

void drawable::GroundMesh::updatePerspective(glm::mat4 viewMatrix)
{
    view = viewMatrix;
}

void drawable::GroundMesh::fillBuffers(GLFWwindow* w)
{
    glfwMakeContextCurrent(w);
    // Bind all the model arrays to the appropriate buffers
    glBindVertexArray(VAO);

    // Vertex buffer contains vertices and indices interleafed
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, interleafed.size()*sizeof(VertexNormal), &interleafed.front(), GL_STATIC_DRAW);

    // Tell the shader how the interleafing should be undone
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexNormal), (void*)offsetof(VertexNormal, position));

    // Enable and set up the "normal" attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexNormal), (void*)offsetof(VertexNormal, normal));

    // Index buffer contains just the indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size()*sizeof(unsigned int), &mIndices.front(), GL_STATIC_DRAW);
}

void drawable::GroundMesh::loadUniforms(GLuint shader)
{
    shaders::setUniformVec(shader, "model", model);
    shaders::setUniformVec(shader, "normalModel", normalModel);
    shaders::setUniformVec(shader, "projection", projection);
    shaders::setUniform(shader, "rockScale", rockScale);
}

drawable::GroundMesh::GroundMesh()
{
}

drawable::GroundMesh::GroundMesh(unsigned int shaderInd, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices)
{
    // Define projection, view, and model matrices
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    model = glm::mat4(1.0f); // Identity matrix for now
    normalModel = glm::mat3(glm::transpose(glm::inverse(model)));
    rockScale = 0.2f;

    lightingMode = 2;

    // Store the model parameters
    mVertices = vertices;
    mIndices = indices;
    normals = computeNormals(vertices, indices);
    interleafed = interleafVertices(vertices, normals);

    // Create a Vertex Buffer Object (VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Save the reference to the shader manager
    shaderProgramIndex = shaderInd;
}

drawable::GroundMesh::~GroundMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

std::vector<drawable::VertexNormal> drawable::interleafVertices(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals)
{
    std::vector<drawable::VertexNormal> interleafed(vertices.size());
    for (int i=0; i<vertices.size(); i++) {
        interleafed[i].position = vertices[i];
        interleafed[i].normal =  normals[i];
    }

    return interleafed;
}

std::vector<glm::vec3> drawable::computeNormals(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices)
{
    std::vector<glm::vec3> normals(vertices.size());
    // printf("indices size: %u\n", indices.size());

    for (int i=0; i<(int)(indices.size()/3); i++) {
        glm::vec3 AB = vertices[indices[3*i+1]] - vertices[indices[3*i]];
        glm::vec3 AC = vertices[indices[3*i+2]] - vertices[indices[3*i]];
        glm::vec3 norm = glm::normalize(glm::cross(AB, AC));
        // if (norm[1] < 0) {
        //     norm = -norm;
        // }
        for (int j=0; j<3; j++) {
            normals[indices[3*i+j]] = norm;
        }
        // printf("normals: [%f, %f, %f]\n", normals[indices[3*i]][0], normals[indices[3*i]][1], normals[indices[3*i]][2]);

    }

    return normals;
}
