#version 330 core
layout (location = 0) in vec3 uiPos;
layout (location = 1) in vec2 cTexCoord;

out vec2 uiTexCoord;

uniform mat4 uiMVP;

void main()
{
    gl_Position = uiMVP * vec4(uiPos, 1.01);
    uiTexCoord = vec2(cTexCoord.x, cTexCoord.y);
}