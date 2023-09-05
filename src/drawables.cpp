#include "drawables.hpp"

void drawable::Drawable::update()
{
}

void drawable::Drawable::draw(GLFWwindow* window)
{
    // glfwMakeContextCurrent(window);
}

drawable::Drawable::Drawable()
{
}

void drawable::ThreeDimMesh::update()
{
    
}

void drawable::ThreeDimMesh::draw(GLFWwindow* window)
{
    // To allow rendering to the visible screen, we need the set the context
    glfwMakeContextCurrent(window);

    // Activate the appropriate shader program
    GLuint shaderProgram = mShaderManager.activateShader(shaderProgramIndex);

    // Get uniform locations for additional parameters
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLuint fogColorLocation = glGetUniformLocation(shaderProgram, "fogColor");
    glUniform3fv(fogColorLocation, 1, glm::value_ptr(fogColor));

    GLuint fogDensityLocation = glGetUniformLocation(shaderProgram, "fogDensity");
    glUniform1f(fogDensityLocation, fogDensity);

    // Update model matrix (rotation)
    // model = glm::rotate(model, (float)glfwGetTime()/1000, glm::vec3(1.0f, 0.5f, 0.2f));
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // Bind all the model arrays to the appropriate buffers
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertSize, mVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, mIndices, GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Bind the vertex data and draw the mesh to the second buffer
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void drawable::ThreeDimMesh::updatePerspective(glm::mat4 viewMatrix)
{
    view = viewMatrix;
}

drawable::ThreeDimMesh::ThreeDimMesh()
{
}

drawable::ThreeDimMesh::ThreeDimMesh(shaders::ShaderManager &shaderManager, unsigned int shaderInd, float* vertices, unsigned int* indices, int numVerts, int numInds)
{
    // Define projection, view, and model matrices
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    model = glm::mat4(1.0f); // Identity matrix for now
    fogColor = glm::vec3(0.5f, 0.5f, 0.5f); // Example fog color (gray)
    fogDensity = 2.0f; // Example fog density (adjust as needed)

    // Store the model parameters
    mVertices = vertices;
    mIndices = indices;
    vertSize = numVerts;
    indSize = numInds;

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
