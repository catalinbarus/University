#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output
out vec2 texcoord;

uniform float time;
uniform bool iQsuad;


void main()
{
    // TODO(student): Pass v_texture_coord as output to fragment shader
    texcoord = v_texture_coord;

	if (time >= 0)
	{
		texcoord = vec2(texcoord.x - time / 10.f, texcoord.y);
	}

	mat4 ModelView = View * Model;

	if (iQsuad == true)
	{
		ModelView[0][0] = 1.f;
		ModelView[0][1] = 0.f;
		ModelView[0][2] = 0.f;

		ModelView[1][0] = 0.f;
		ModelView[1][1] = 1.f;
		ModelView[1][2] = 0.f;

		ModelView[2][0] = 0.f;
		ModelView[2][1] = 0.f;
		ModelView[2][2] = 1.f;
	}

    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
