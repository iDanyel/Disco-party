#version 330

// Input
in vec4 fragmentColor;

// Output
layout(location = 0) out vec4 outputColor;

void main() {
    outputColor = fragmentColor;
}
