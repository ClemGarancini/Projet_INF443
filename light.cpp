#include "light.hpp"
#include <math.h>

using namespace cgp;

//hierarchy_mesh_drawable create_light(vec3 position) {
//
//}


mesh create_support() {
	mesh support = mesh_primitive_cylinder(0.015f, vec3{ 0,0,0 }, vec3{ 0,1,0 });
	support.push_back(mesh_primitive_cone(0.015f, 0.012f, vec3{ 0,1,0 }, vec3{ 0,1,0 }));
	
	mesh round_support;
	round_support.position.resize(1000);

	float theta_i = Pi / 99;
	float theta_j = 2*Pi / 9;
	float ray_maj = 0.1f;
	float ray_min = 0.01f;
	vec3 p_base = { 0.1f,0.8f,0 };


	for (int i = 0;i < 100;i++) {
		vec3 normal = { cos(theta_i * i),sin(theta_i * i) ,0 };
		vec3 p_i = p_base + ray_maj * normal;
		for (int j = 0;j < 10;j++) {
			vec3 p_ij = p_i + ray_min * (cos(theta_j * j) * normal + vec3{ 0,0,sin(theta_j * j) });
			round_support.position[i * 10 + j] = p_ij;
		}
	}

	round_support.connectivity.resize(99 * 10 * 2);
	for (int i = 0; i < 99; i++) {
		for (int j = 0;j < 9;j++) {
			round_support.connectivity[2 * (i * 10 + j)] = { 10 * i + j,10 * (i + 1) + j,10 * (i + 1) + j + 1 };
			round_support.connectivity[2 * (i * 10 + j) + 1] = { 10 * i + j ,10 * (i + 1) + j + 1 ,10 * i + j+1 };
		}
		round_support.connectivity[2 * (i * 10 + 9)] = { 10 * i + 9,10 * (i + 1) + 9,10 * (i + 1) };
		round_support.connectivity[2 * (i * 10 + 9) + 1] = { 10 * i + 9 ,10 * (i + 1) ,10 * i };
	}


	round_support.fill_empty_field();
	support.push_back(round_support);

	support.push_back(mesh_primitive_cone(2 * ray_min, 0.04f, p_base + ray_maj * vec3{ 1,0,0 } + vec3{ 0,-0.02f,0 }, { 0,1,0 }, false));
	return support;
}

void compute_light(vec3 position,scene_environment_with_multiple_lights& environment) {
	environment.spotlight_color[0] = { 0.8f, 0.8f, 1.0f };
	environment.spotlight_position[0] = position + vec3{ 0.2f,0.8f,0 };

}