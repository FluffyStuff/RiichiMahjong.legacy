#version 330 core
#define MAX_LIGHTS 2

struct lightSourceParameters 
{
	vec3 position;
	vec3 color;
	float intensity;
	/*vec3 spotDirection;*/
};

uniform mat4 projection_transform;
uniform mat4 view_transform;
uniform mat4 model_transform;

uniform int light_count;
uniform lightSourceParameters light_source[MAX_LIGHTS];

in vec4 position;
in vec3 texture_coord;
in vec3 normal;

out vec2 frag_texture_coord;
out vec3 frag_normal;
out vec3 frag_camera_normal;

out vec3 light_normals[MAX_LIGHTS];
out float light_intensity[MAX_LIGHTS];
out vec3 light_colors[MAX_LIGHTS];

void main()
{
	vec3 mod_pos = (model_transform * position).xyz;
	for (int i = 0; i < light_count; i++)
	{
		light_normals[i] = light_source[i].position - mod_pos;
		light_intensity[i] = light_source[i].intensity;
		light_colors[i] = light_source[i].color;
	}
	
	frag_texture_coord = texture_coord.xy;
	frag_normal = (vec4(normalize(normal), 1.0) * inverse(model_transform)).xyz;
	frag_camera_normal = inverse(view_transform)[3].xyz - mod_pos;
	gl_Position = projection_transform * view_transform * model_transform * position;
}