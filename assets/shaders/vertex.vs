#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 uOffSet;

void main() {
    gl_Position = vec4(aPos.x + uOffSet.x, aPos.y + uOffSet.y, aPos.z, 1.0);
}