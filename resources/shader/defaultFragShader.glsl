#version 420 core

in vec2 texCoord;
in vec4 vertColor;

out vec4 fragColor;

void main() {
    fragColor = vertColor;
}
