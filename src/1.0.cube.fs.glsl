#version 330 core
in vec3 myColor;
in vec2 myTexCoord;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
//    FragColor = vec4(myColor, 1.0f);
    FragColor = texture(texture1, myTexCoord);
}
