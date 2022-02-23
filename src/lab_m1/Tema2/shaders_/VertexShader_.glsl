#version 330

// Input
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 objectColor;
uniform bool deformation;
uniform float engineTime;

uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// Output
out vec3 fragmentPosition;
out vec3 fragmentColor;

vec3 getDeformedVertexPosition() {
    float x = vertexPosition.x, y = vertexPosition.y, z = vertexPosition.z;

    return vec3(x, y, z) * (1 + abs(cos(engineTime / (x + y + z))) * (x + y + z) / 4);
}

void main() {
    // Compute light
    vec3 world_position = vec3(Model * vec4(vertexPosition, 1));
    vec3 N = normalize(vec3(Model * vec4(vertexNormal, 0)));
    vec3 V = normalize(eye_position - world_position);
    vec3 L = normalize(light_position - world_position);
    vec3 H = normalize(L + V);
    float light_intensity = 50;
    vec3 light_color = vec3(1, 1, 1);

    float ambient_light = 0.95 * material_kd;
    float diffuse_light = material_kd * light_intensity * max(dot(N, L), 0);
    float specular_light = 0;

    if (diffuse_light > 0)
        specular_light = material_ks * light_intensity * pow(max(dot(N, H), 0), material_shininess);

    float light = ambient_light + (diffuse_light + specular_light) / (distance(light_position, world_position) + 1);

    // Set fragment color
    fragmentPosition = vertexPosition;
    fragmentColor = objectColor * light_color * light;

    // Deform vertex if needed
    if (!deformation)
        gl_Position = Projection * View * Model * vec4(vertexPosition, 1.0);
    else
        gl_Position = Projection * View * Model * vec4(getDeformedVertexPosition(), 1.0);
}
