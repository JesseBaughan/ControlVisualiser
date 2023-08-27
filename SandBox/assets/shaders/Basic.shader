#shader vertex
#version 330

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;

out vec3 v_Position;

void main() 
{
    v_Position = a_Position;
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
};

#shader fragment
#version 330

layout(location = 0) out vec4 colour;

in vec3 v_Position;

void main() 
{
    colour = vec4(0.2, 0.3, 0.8, 1.0);
};