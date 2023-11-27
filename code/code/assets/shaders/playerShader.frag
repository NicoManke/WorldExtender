#version 330 core
out vec4 pFragColor;
  
in vec2 pTexCoord;

uniform sampler2D playerTexture;

void main()
{
    pFragColor = texture(playerTexture, pTexCoord);
}