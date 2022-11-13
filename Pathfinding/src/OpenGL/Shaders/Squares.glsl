#shader vertex
#version 460 core

in layout(location = 0) vec2 position;
in layout(location = 1) vec2 offset;

in layout(location = 2) vec3 color;
out vec3 u_Color;

void main()
{
	u_Color = color;
	gl_Position = vec4(position + offset, 0, 1);
};

#shader fragment
#version 460 core

in vec3 u_Color;
out vec4 color;

void main()
{
	color = vec4(u_Color.r, u_Color.g, u_Color.b, 1.0f);
};