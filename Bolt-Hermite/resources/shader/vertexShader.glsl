#version 420 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

out VS_OUT {
    vec4 vertColor;
} vs_out;

uniform mat4 model;

layout(std140, binding = 0) uniform Matrices {
    mat4 proj;
};

void main() {
    gl_Position = proj * model * vec4(aPos, 1.f);
    vs_out.vertColor = aColor;
}
