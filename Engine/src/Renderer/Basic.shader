#version 330

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Colour;

out vec3 v_Position;
out vec4 v_Colour;

void main() 
{
    v_Position = a_Position;
    v_Colour = a_Colour;
    gl_Position = vec4(a_Position, 1.0);
};

#version 330

layout(location = 0) out vec4 colour;

in vec3 v_Position;
in vec4 v_Colour;

void main() 
{
    colour = vec4(v_Position * 0.5 + 0.5 , 1.0);
    colour = v_Colour;
};