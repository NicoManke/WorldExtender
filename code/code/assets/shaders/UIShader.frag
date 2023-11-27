#version 330 core
out vec4 uiFragColor;
  
in vec2 uiTexCoord;

uniform sampler2D uiTexture;

void main()
{
    uiFragColor = texture(uiTexture, uiTexCoord);
}