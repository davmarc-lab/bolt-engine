#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec3 aPosOffset;
layout (location = 5) in vec4 aColorOffset;

out vec4 vertColor;

layout(std140, binding = 0) uniform Matrices {
    mat4 proj;
};

void main() {
    gl_Position = proj * vec4(aPos + aPosOffset, 1.0f);
    vertColor = aColorOffset;
}
