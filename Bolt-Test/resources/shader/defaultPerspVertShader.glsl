#version 420 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

out VS_OUT {
    vec4 vertColor;
    vec2 texCoord;
    vec3 normal;
} vs_out;

out vec3 FragPos;

uniform mat4 view;
uniform mat4 model;

layout(std140, binding = 0) uniform Matrices {
    mat4 proj;
};

void main() {
    FragPos = vec3(model * vec4(aPos, 1.f));
    gl_Position = proj * model * vec4(aPos, 1.0f);
    vs_out.vertColor = aColor;
    vs_out.texCoord = aTexCoord;
    vs_out.normal = aNormal;
}
