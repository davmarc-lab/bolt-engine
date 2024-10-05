#version 420 core

in vec2 texCoord;
in vec4 vertColor;

out vec4 fragColor;

void main() {
    if (gl_FrontFacing) {
        fragColor = vertColor;
    }
    else {
        fragColor = vec4(0, 0, 0, 1);
    }
}
