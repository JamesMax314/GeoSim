    #version 330 core
    out vec4 FragColor;
    in vec3 FragPos;
    vec3 FragC;
    uniform vec3 fogColor; // The color of the fog
    uniform float fogDensity; // Adjusts fog density (higher values increase fog effect)
    void main()
    {
        FragC = vec3(1.0f, 0.5f, 0.5f);
        float distance = length(FragPos); // Distance from the camera to the fragment
        float fogFactor = 1.0f - exp(-fogDensity * distance * distance); // Calculate fog factor
        fogFactor = clamp(fogFactor, 0.0f, 1.0f); // Clamp the fog factor to the range [0, 1]
        
        vec3 finalColor = mix(vec3(FragC), fogColor, fogFactor); // Mix the original color with fog color
        FragColor = vec4(finalColor, 1.0f); // Set the fragment color with fog
        // FragColor = vec4(fogFactor, 0.5f, 0.5f, 1.0f);
    }