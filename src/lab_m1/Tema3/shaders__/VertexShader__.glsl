#version 330

// Input
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 textureCoordinates;

// Output
out vec2 texCoord;
out vec3 worldPos;
out vec3 normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
	worldPos = vec3(Model * vec4(vertexPosition, 1));
    normal = normalize(vec3(Model * vec4(vertexNormal, 0)));

	texCoord = textureCoordinates;
	gl_Position = Projection * View * Model * vec4(vertexPosition, 1.0);
}
