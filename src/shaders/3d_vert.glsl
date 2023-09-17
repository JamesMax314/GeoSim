    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormals;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    out vec3 FragPos; // The vertex's position in world coordinates (for fog calculation)
    out vec3 normal;
    void main()
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        FragPos = vec3(model * vec4(aPos, 1.0)); // Calculate FragPos in world coordinates
        normal = aNormals;
    }