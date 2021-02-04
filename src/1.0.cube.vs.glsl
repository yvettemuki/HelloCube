#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 myColor;
out vec2 myTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
vec3 color1 = vec3(61.0f/255.0f, 126.0f/255.0f, 170.0f/255.0f);
vec3 color2 = vec3(142.0f/255.0f, 84.0f/255.0f, 233.0f/255.0f);

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    if (time != 1) {
        float interpolated = time - int(time);
        myColor = mix(color1, color2, interpolated);
    } else {
        myColor = aColor;
    }
    myTexCoord = aTexCoord;
}