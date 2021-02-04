#version 330 core
in vec3 myColor;
in vec2 myTexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform int shaderType;

void main()
{
    if (shaderType == 0)
    {
        FragColor = vec4(myColor, 1.0f);
    }
    else if (shaderType == 1)
    {

        FragColor = texture(texture1, myTexCoord);
    }
}
