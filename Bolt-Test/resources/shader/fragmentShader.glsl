#version 420 core

in VS_OUT {
    vec4 vertColor;
} fs_out;

out vec4 fragColor;

void main() {
    fragColor = fs_out.vertColor;
}