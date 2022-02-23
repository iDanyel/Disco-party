#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_position;
in vec3 frag_color;
in vec2 frag_coord;
in vec3 frag_normal;
in float _engineTime;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Write pixel out color
    out_color = vec4(frag_normal * vec3(abs(sin(_engineTime)), abs(cos(_engineTime)), abs(cos(_engineTime) / (sin(_engineTime) + 0.01))), 1);
}
