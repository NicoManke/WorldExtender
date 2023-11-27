#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 bTexCoord;

out vec2 pTexCoord;

uniform mat4 playerMVP;

void main()
{
    gl_Position = playerMVP * vec4(aPos, 1.01);
    pTexCoord = vec2(bTexCoord.x, bTexCoord.y);
}