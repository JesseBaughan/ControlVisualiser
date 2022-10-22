#shader vertex
#version 330

in vec3 vp;

uniform mat4 u_MVP;

void main() 
{
  gl_Position = u_MVP * vec4(vp, 1.0);
};

#shader fragment
#version 330

out vec4 frag_colour;

void main() 
{
  frag_colour = vec4(1.0f, 0.5f, 0.2f, 1.0f);
};