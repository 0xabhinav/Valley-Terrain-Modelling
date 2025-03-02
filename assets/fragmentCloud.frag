#version 300 es
precision highp float;
out vec4 fragColor;
in vec2 texCoord;
uniform sampler2D theTexture;
void main()
{
    fragColor = texture(theTexture,texCoord);
}