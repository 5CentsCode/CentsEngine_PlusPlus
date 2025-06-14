#version 400 core

in vec2 TexCoord;

uniform sampler2D uTexture;

out vec4 FragColor;

void main()
{
	FragColor = texture(uTexture, TexCoord);
}