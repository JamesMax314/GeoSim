#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 normal;

uniform float rockScale; // Adjusts how quickly grass changes to rocks
uniform vec3 lightColour;
uniform vec3 lightLocation;
vec3 lightLoc;

vec3 lightDir;

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
    // Compute ambiant
    float ambientStrength = 0.1;
    vec3 ambient = lightColour*ambientStrength;

    // Compute Diffuse
    lightDir = normalize(lightLocation - FragPos);
    float diff = max(dot(lightDir, normal), 0.0);

    vec3 groundColour = mountainColour(FragPos);

    vec3 result = (diff + ambient) * groundColour;
    FragColor = vec4(result, 1.0);
}


