#version 420 core

out vec4 fragColor;
in vec4 vertColor;

void main() {
    fragColor = vertColor;
}
