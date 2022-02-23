#version 330

// Input
in vec2 texCoord;
in vec3 worldPos;
in vec3 normal;

// Output
layout(location = 0) out vec4 outputColor;

// Uniform properties
uniform bool lightCellIlluminationMode;
uniform bool reflectorIlluminationMode;
uniform bool discoBalllIlluminationMode;

uniform float kd;
uniform float ks;
uniform float shininess;
uniform float cutOffAngle;
uniform float lightRadius;
uniform float discoBallRotationTime;
uniform vec3 eyePos;

uniform bool simple;
uniform bool transparent;

uniform vec3 objectColor;
uniform sampler2D texture;
uniform bool isTextured;

uniform bool lightCell;
uniform vec3 lightCellPos[9];
uniform vec3 lightCellColor[9];
uniform float lightCellIntensity[9];

uniform bool reflector;
uniform vec3 reflectorPos[4];
uniform vec3 reflectorColor[4];
uniform vec3 reflectorDir[4];
uniform float reflectorIntensity[4];

uniform bool discoBall;
uniform vec3 discoBallPos;
uniform float discoBallIntensity;

vec3 lightCellContribution(const vec3 lightCellPos, const vec3 lightCellColor, const float lightCellIntensity) {
    vec3 N = normalize(normal);
    vec3 V = normalize(eyePos - worldPos);
    vec3 L = normalize(lightCellPos - worldPos);
    vec3 H = normalize(L + V);

    float lightAttFactor = 0.0f;
    float dist = distance(worldPos, lightCellPos);

    if (dist < lightRadius)
	    lightAttFactor = pow(lightRadius - dist, 2);

    float diffuseLight = kd * lightCellIntensity * max(dot(N, L), 0);
    float specularLight = 0;

    if (diffuseLight > 0)
        specularLight = ks * lightCellIntensity * pow(max(dot(N, H), 0), shininess);

    return lightCellColor * lightAttFactor * (diffuseLight + specularLight);
}

vec3 reflectorContribution(const vec3 reflectorPos, const vec3 reflectorColor, const vec3 reflectorDir, const float reflectorIntensity) {
    vec3 N = normalize(normal);
    vec3 V = normalize(eyePos - worldPos);
    vec3 L = normalize(reflectorPos - worldPos);
    vec3 H = normalize(L + V);

    float diffuseLight = kd * reflectorIntensity * max(dot(N, L), 0);
    float specularLight = 0;

    if (diffuseLight > 0)
         specularLight = ks * reflectorIntensity * pow(max(dot(N, H), 0), shininess);

    float spotlight = dot(-L, reflectorDir);
    float spotlightLimit = cos(cutOffAngle);

    float lightAttFactor;
 
    if (spotlight > spotlightLimit)
        lightAttFactor = pow((spotlight - spotlightLimit) / (1 - spotlightLimit), 2);

    return reflectorColor * lightAttFactor * (diffuseLight + specularLight) / (distance(reflectorPos, worldPos) + 1);
}

vec3 discoBallContribution() {
    // Get color
    vec3 lightDir = worldPos - discoBallPos;
    vec2 texCoordinates;

    texCoordinates.x = (1.0 / (2 * 3.14159)) * atan (lightDir.x, lightDir.z) + 0.1f * discoBallRotationTime;
    texCoordinates.y = (1.0 / 3.14159) * acos (lightDir.y / length (lightDir));

    vec3 discoBallColor = texture2D(texture, texCoordinates).xyz;

    // Compute light
    vec3 N = normalize(normal);
    vec3 V = normalize(eyePos - worldPos);
    vec3 L = normalize(discoBallPos - worldPos);
    vec3 H = normalize(L + V);

    float lightAttFactor = 0.0f;
    float dist = distance(worldPos, discoBallPos);

    if (dist < lightRadius)
	    lightAttFactor = pow(lightRadius - dist, 2);

    float diffuseLight = kd * discoBallIntensity * max(dot(N, L), 0);
    float specularLight = 0;

    if (diffuseLight > 0)
        specularLight = ks * discoBallIntensity * pow(max(dot(N, H), 0), shininess);

    return discoBallColor * (diffuseLight + specularLight) / (distance(discoBallPos, worldPos) + 1);
}

void main() {
    if (isTextured) {
        vec2 texCoordinates = texCoord;

        texCoordinates.x += 0.1f * discoBallRotationTime;
        outputColor = texture2D(texture, texCoordinates);
        return;
    }

    vec3 color = vec3(0, 0, 0);
    float alpha = 1;

    if (simple) {
        color = objectColor;

        if (transparent)
            alpha = 0.5f;
    }

    if (lightCell && lightCellIlluminationMode)
        for (int i = 0; i < 9; i++)
            color += lightCellContribution(lightCellPos[i], lightCellColor[i], lightCellIntensity[i]);
    
    if (reflector && reflectorIlluminationMode)
        for (int i = 0; i < 4; i++)
            color += reflectorContribution(reflectorPos[i], reflectorColor[i], reflectorDir[i], reflectorIntensity[i]);

    if (discoBall && discoBalllIlluminationMode)
        color += discoBallContribution();

    outputColor = vec4(color, alpha);
}
