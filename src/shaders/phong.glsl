#version 330 core
out vec4 FragColor;
in vec3 FragPos;

uniform float rockScale; // Adjusts how quickly grass changes to rocks
uniform vec3 lightColour;

vec3 mountainColour(vec3 fragPos)
{
    vec3 FragC = vec3(0.5f, 1.0f, 0.5f);
    vec3 RockC = vec3(0.5f, 0.5f, 0.5f);
    vec3 SeaC = vec3(0.5f, 0.5f, 1.0f);
    float rockStrength = rockScale*fragPos[1]; // Calculate how rocky based on height
    float seaStrength = -rockStrength;
    seaStrength = clamp(seaStrength, 0.0f, 1.0f);
    rockStrength = clamp(rockStrength, 0.0f, 1.0f); // Clamp the fog factor to the range [0, 1]
    
    vec3 finalColor = mix(vec3(FragC), RockC, rockStrength); // Mix the original color with fog color
    finalColor = mix(vec3(finalColor), SeaC, seaStrength);
    
    return finalColor;
}

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = lightColour*ambientStrength;

    vec3 groundColour = mountainColour(FragPos);

    vec3 result = ambient * groundColour;
    FragColor = vec4(result, 1.0);
}


