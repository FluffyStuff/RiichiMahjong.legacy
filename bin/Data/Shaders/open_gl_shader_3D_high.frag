#version 120
#define MAX_LIGHTS 2

uniform bool use_texture;
uniform sampler2D tex;
uniform int light_count;

varying vec2 frag_texture_coord;
varying vec3 frag_normal;
varying vec3 frag_camera_normal;

varying vec3 light_normals[MAX_LIGHTS];
varying float light_intensity[MAX_LIGHTS];
varying vec3 light_colors[MAX_LIGHTS];

// Material
uniform vec4 ambient_color;
uniform float ambient_material_multiplier;

uniform vec4 diffuse_color;
uniform float diffuse_material_multiplier;

uniform vec4 specular_color;
uniform float specular_material_multiplier;

uniform float specular_exponent;
uniform float alpha;

/* BLEND_TYPE
	COLOR = 0,
    MATERIAL = 1,
    BLEND = 2,
	HYBRID = 3
*/

/*vec4 color_blend(vec4 color_src, vec4 color_dst, int blend_type)
{
	switch (blend_type)
	{
	default:
	case 0:
		return color_src;
	case 1:
		return color_dst;
	case 2:
		return vec4(color_src.xyz * color_dst.a + color_dst.xyz * color_dst.a, max(color_src.a, color_dst.a));
	case 3:
		//return vec4(0.0, 0.0, 0.0, 1.0);
		return vec4(color_src.xyz * min(color_src.a, color_dst.a) + color_dst.xyz * min(color_src.a, color_dst.a) * 1.0, max(color_src.a, color_dst.a));
	}
}*/

vec4 calculate_lighting_factor(vec4 diffuse_in, vec4 specular_in)
{		
	float blend_factor = 0.0;//0.005;
	float constant_factor = 0.01;
	float linear_factor = 0.8;
	float quadratic_factor = 0.5;
		
	vec3 normal = normalize(frag_normal);
	
	vec3 diffuse = vec3(0);//diffuse_in;//out_color.xyz * 0.02;
	vec3 specular = vec3(0);
	vec3 c = diffuse_in.xyz;//out_color.xyz;
	
	for (int i = 0; i < light_count; i++)
	{
		float intensity = light_intensity[i];
		
		float lnlen = max(length(light_normals[i]), 1);
		vec3 ln = normalize(light_normals[i]);
		vec3 cm = normalize(frag_camera_normal);
		
		float d = max(dot(normal, ln) / 1, 0);
		float plus = 0;
		plus += d * constant_factor;
		plus += d / lnlen * linear_factor;
		plus += d / pow(lnlen, 2) * quadratic_factor;
		
		diffuse += (c * (1-blend_factor) + light_colors[i] * blend_factor) * plus * intensity;
		
		if (dot(ln, normal) > 0) // Only reflect on the correct side
		{
			float s = max(dot(cm, reflect(-ln, normal)), 0);
			float spec = pow(s, specular_exponent);
			
			float p = 0;
			p += spec * constant_factor;
			p += spec / lnlen * linear_factor;
			p += spec / pow(lnlen, 2) * quadratic_factor;
			
			p = max(p, 0) * intensity;
			
			specular += (light_colors[i] * (1-blend_factor) * 0 + specular_in.xyz/* * blend_factor*/) * p;
		}
	}
	
	vec4 out_color = vec4(0.0, 0.0, 0.0, 1.0);
	out_color.xyz = diffuse + specular;
	
	out_color.xyz /= max(pow(length(frag_camera_normal) / 5, 1.0) / 10, 1);
	//out_color.a *= alpha;
	
	return out_color;
}

void main()
{
	if (alpha <= 0)
		discard;
	
	vec4 t = use_texture ? texture2D(tex, frag_texture_coord) : vec4(0);
	
	vec4 ambient = ambient_color * ambient_color.a * (1 - t.a) + t * ambient_material_multiplier;
	vec4 diffuse = diffuse_color * diffuse_color.a * (1 - t.a) + t * diffuse_material_multiplier;
	//vec4 ambient = ambient_color * ambient_color.a + tex * ambient_material_multiplier; //color_blend(ambient_color, texture2D(tex, frag_texture_coord), ambient_blend_type);
	//vec4 diffuse = diffuse_color * diffuse_color.a + tex * diffuse_material_multiplier; //color_blend(diffuse_color, texture2D(tex, frag_texture_coord), diffuse_blend_type);
	vec4 specular = specular_color * specular_color.a + t * specular_material_multiplier; //color_blend(specular_color, texture2D(tex, frag_texture_coord), specular_blend_type);
	specular *= 1;
	
	if (ambient.a <= 0 && diffuse.a <= 0)
		discard;
	
	vec4 lighting_factor = calculate_lighting_factor(diffuse, specular);
	
	vec4 out_color = ambient + lighting_factor;
	if (out_color.a <= 0)
		discard;
	
	out_color.a *= alpha;
	
	gl_FragColor = out_color;
}