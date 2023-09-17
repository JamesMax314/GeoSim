#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 normal;

uniform float rockScale; // Adjusts how quickly grass changes to rocks
uniform vec3 lightColour;
uniform vec3 lightLocation;
uniform vec3 viewPos;

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

vec3 phong() {
    // Compute ambiant
    float ambientStrength = 0.1;

    // Compute Diffuse
    lightDir = normalize(lightLocation - FragPos);
    float diff = max(dot(lightDir, normal), 0.0);

    // Compute Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal); 
    float spec = specularStrength*pow(max(dot(viewDir, reflectDir), 0.0), 32); 

    vec3 lighting = (spec + diff + ambientStrength)*lightColour;

    return lighting;
}

vec3 blingPhong() {
        // Compute ambiant
    float ambientStrength = 0.1;

    // Compute Diffuse
    lightDir = normalize(lightLocation - FragPos);
    float diff = max(dot(lightDir, normal), 0.0);

    // Compute Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec3 reflectDir = reflect(-lightDir, normal); 
    float spec = specularStrength*pow(max(dot(viewDir, halfwayDir), 0.0), 32); 

    vec3 lighting = (spec + diff + ambientStrength)*lightColour;

    return lighting;
}

void main() {
    vec3 lighting = blingPhong();

    vec3 groundColour = mountainColour(FragPos);

    vec3 result = lighting * groundColour;
    FragColor = vec4(result, 1.0);
}


