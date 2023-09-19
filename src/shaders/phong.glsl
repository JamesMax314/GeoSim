#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 normal;

uniform float rockScale; // Adjusts how quickly grass changes to rocks
uniform vec3 lightColour;
uniform vec3 lightLocation;
uniform vec3 viewPos;
uniform int lightingMode;
uniform int colourMode;

vec3 lightLoc;
vec3 lighting;
vec3 lightDir;

vec3 groundColour;

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

vec3 mountainColourGrad()
{
    vec3 GrassC = vec3(0.251, 0.4824, 0.251);
    vec3 RockC = vec3(0.6039, 0.4, 0.3137);
    // vec3 SeaC = vec3(0.5, 0.5, 1.0);
    vec3 vert = vec3(0.0f, 1.0f, 0.0f);

    float rockStrength = (1-dot(normalize(normal), vert)); // Calculate how rocky based on height
    rockStrength = clamp(rockStrength, 0.0f, 1.0f); // Clamp the fog factor to the range [0, 1]
    
    vec3 finalColor = mix(GrassC, RockC, rockStrength); // Mix the original color with fog color
    
    return finalColor;
}

vec3 basic() {
    return vec3(1.0f, 1.0f, 1.0f);
}

vec3 phong() {
    // Compute ambiant
    float ambientStrength = 0.1;

    // Compute Diffuse
    lightDir = normalize(lightLocation - FragPos);
    float diff = max(dot(lightDir, normal), 0.0);

    // Compute Specular
    float specPow = 3;
    float specularStrength = 0.1;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal); 
    float spec = specularStrength*pow(max(dot(viewDir, reflectDir), 0.0), specPow); 

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
    float specPow = 3;
    float specularStrength = 0.1;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = specularStrength*pow(max(dot(normal, halfwayDir), 0.0), specPow); 

    vec3 lighting = (spec + diff + ambientStrength)*lightColour;

    return lighting;
}

void main() {
    if (lightingMode == 0) {
        lighting = basic();
    } else if (lightingMode == 1) {
        lighting = phong();
    } else if (lightingMode == 2) {
        lighting = blingPhong();
    }

    if (colourMode == 0) {
        groundColour = mountainColour(FragPos);
    } else if (colourMode == 1) {
        groundColour = mountainColourGrad();
    } 

    vec3 result = lighting * groundColour;
    FragColor = vec4(result, 1.0);
}


