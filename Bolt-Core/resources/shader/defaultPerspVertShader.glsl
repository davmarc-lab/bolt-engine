#version 420 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec4 vertColor;
out vec2 texCoord;

uniform mat4 view;
uniform mat4 model;

layout(std140, binding = 0) uniform Matrices {
    mat4 proj;
};

void main() {
    gl_Position = proj * view * model * vec4(aPos, 1.0f);
    vertColor = aColor;
    texCoord = aTexCoord;
}
