#include "road.hpp"
#include <vector>
#include <iostream>
#include "Spline curves/key_positions_structure.hpp"
#include "Spline curves/interpolation.hpp"

using namespace cgp;

mesh create_road_mesh(std::vector<vec3> points,int N_samples_per_point,float offset) {
	mesh road;

	int N_samples_tot = N_samples_per_point * (points.size()-3);
	road.position.resize(2*N_samples_tot);


	vec3 prec_interpol = points[1];
	vec3 curr_interpol = points[1];
	vec3 curr_path = normalize(points[2]-points[0]);
	vec3 interpol_left = curr_interpol + offset * vec3{ -curr_path.z,curr_path.y,curr_path.x };
	vec3 interpol_right = curr_interpol + offset * vec3{ curr_path.z,curr_path.y,-curr_path.x };
	road.position[0] = interpol_left;
	road.position[1] = interpol_right;

	for (int i = 1;i < N_samples_tot;i++) {
		
		int curr_point = i / N_samples_per_point + 1;
		float t = static_cast<float>(i % N_samples_per_point) / static_cast<float>(N_samples_per_point) + 1.0f;

		

		vec3 const& p0 = points[curr_point - 1];
		vec3 const& p1 = points[curr_point];
		vec3 const& p2 = points[curr_point + 1];
		vec3 const& p3 = points[curr_point + 2];

		curr_interpol = cardinal_spline_interpolation(t, 0.0f, 1.0f, 2.0f, 3.0f, p0, p1, p2, p3, 0.5f);

		curr_path = normalize(curr_interpol - prec_interpol);
		prec_interpol = curr_interpol;

		interpol_left = curr_interpol + offset*vec3{ -curr_path.z,curr_path.y,curr_path.x };
		interpol_right = curr_interpol + offset * vec3{ curr_path.z,curr_path.y,-curr_path.x };

		road.position[2 * i] = interpol_left;
		road.position[2 * i + 1] = interpol_right;
	}

	road.connectivity.resize((N_samples_tot - 1) * 2);
	for (int i = 0;i < N_samples_tot - 1;i++) {
		road.connectivity[2 * i] = { 2 * i,2 * i + 1,2 * i + 3 };
		road.connectivity[2 * i+1] = { 2 * i,2 * i + 3,2 * i + 2 };
	}

	road.uv.resize(N_samples_tot * 2);
	for (int i = 0; i < N_samples_tot; i++) {
		float u = static_cast<float>(i) / static_cast<float>(3);
		road.uv[2*i] = { u,0 };
		road.uv[2*i+1] = { u,1 };
	}



	road.fill_empty_field();
	return road;
}

