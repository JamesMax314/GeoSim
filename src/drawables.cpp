#include "drawables.hpp"

void drawable::Drawable::update()
{
}

void drawable::Drawable::draw(GLFWwindow* window, camera::Camera cam)
{
    // glfwMakeContextCurrent(window);
}

drawable::Drawable::Drawable()
{
}

void drawable::ThreeDimMesh::update()
{
    
}

void drawable::ThreeDimMesh::draw(GLFWwindow* window, camera::Camera cam)
{
    // To allow rendering to the visible screen, we need the set the context
    glfwMakeContextCurrent(window);

    view = cam.viewMatrix;

    // Activate the appropriate shader program
    GLuint shaderProgram = mShaderManager.activateShader(shaderProgramIndex);

    // Get uniform locations for additional parameters
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLuint rockScaleLocation = glGetUniformLocation(shaderProgram, "rockScale");
    glUniform1f(rockScaleLocation, rockScale);

    GLuint lightColourLocation = glGetUniformLocation(shaderProgram, "lightColour");
    glUniform3fv(lightColourLocation, 1, glm::value_ptr(lightColor));

    GLuint lightPosLocation = glGetUniformLocation(shaderProgram, "lightLocation");
    glUniform3fv(lightPosLocation, 1, glm::value_ptr(lightPos));

    // GLuint fogColorLocation = glGetUniformLocation(shaderProgram, "fogColor");
    // glUniform3fv(fogColorLocation, 1, glm::value_ptr(fogColor));

    // GLuint fogDensityLocation = glGetUniformLocation(shaderProgram, "fogDensity");
    // glUniform1f(fogDensityLocation, fogDensity);

    // Update model matrix (rotation)
    // model = glm::rotate(model, (float)glfwGetTime()/1000, glm::vec3(1.0f, 0.5f, 0.2f));
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // Bind all the model arrays to the appropriate buffers
    glBindVertexArray(VAO);

    // Vertex buffer contains vertices and indices interleafed
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, interleafed.size()*sizeof(Vertex), &interleafed.front(), GL_STATIC_DRAW);

    // Tell the shader how the interleafing should be undone
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    // Enable and set up the "normal" attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Index buffer contains just the indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size()*sizeof(unsigned int), &mIndices.front(), GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // Bind the vertex data and draw the mesh to the second buffer
    // glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void drawable::ThreeDimMesh::updatePerspective(glm::mat4 viewMatrix)
{
    view = viewMatrix;
}

drawable::ThreeDimMesh::ThreeDimMesh()
{
}

drawable::ThreeDimMesh::ThreeDimMesh(shaders::ShaderManager &shaderManager, unsigned int shaderInd, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices)
{
    // Define projection, view, and model matrices
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    model = glm::mat4(1.0f); // Identity matrix for now
    fogColor = glm::vec3(0.5f, 0.5f, 0.5f); // Example fog color (gray)
    fogDensity = 0.0f; // Example fog density (adjust as needed)
    rockScale = 0.2f;
    lightColor = {1.0f, 1.0f, 0.0f};
    lightPos = {0.0f, 1.0f, 0.0f};

    // Store the model parameters
    mVertices = vertices;
    mIndices = indices;
    normals = computeNormals(vertices, indices);
    // interleafed = interleafVertices(mVertices, normals);

    // Create a Vertex Buffer Object (VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Save the reference to the shader manager
    mShaderManager = shaderManager;
    shaderProgramIndex = shaderInd;
}

drawable::ThreeDimMesh::~ThreeDimMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

std::vector<drawable::Vertex> drawable::interleafVertices(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals)
{
    std::vector<drawable::Vertex> interleafed(vertices.size());
    for (int i=0; i<vertices.size(); i++) {
        interleafed[i].position = vertices[i];
        interleafed[i].normal =  normals[i];
    }

    return interleafed;
}

std::vector<glm::vec3> drawable::computeNormals(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices)
{
    std::vector<glm::vec3> normals(vertices.size());

    for (int i=0; i<indices.size(); i++) {
        glm::vec3 AB = glm::normalize(vertices[i+1] - vertices[i]);
        glm::vec3 AC = glm::normalize(vertices[i+2] - vertices[i]);
        normals[i] = glm::cross(AB, AC);
    }

    return normals;
}
