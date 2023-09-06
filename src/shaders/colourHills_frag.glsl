  #version 330 core
    out vec4 FragColor;
    in vec3 FragPos;
    vec3 FragC;
    vec3 RockC;
    vec3 SeaC;
    uniform float rockScale; // Adjusts fog density (higher values increase fog effect)
    void main()
    {
        FragC = vec3(0.5f, 1.0f, 0.5f);
        RockC = vec3(0.5f, 0.5f, 0.5f);
        SeaC = vec3(0.5f, 0.5f, 1.0f);
        float rockStrength = rockScale*FragPos[1]; // Calculate how rocky based on height
        float seaStrength = -rockStrength;
        seaStrength = clamp(seaStrength, 0.0f, 1.0f);
        rockStrength = clamp(rockStrength, 0.0f, 1.0f); // Clamp the fog factor to the range [0, 1]
        
        vec3 finalColor = mix(vec3(FragC), RockC, rockStrength); // Mix the original color with fog color
        finalColor = mix(vec3(finalColor), SeaC, seaStrength);
        FragColor = vec4(finalColor, 1.0f); // Set the fragment color with fog
        // FragColor = vec4(fogFactor, 0.5f, 0.5f, 1.0f);
    }