#pragma once
#include "cgp/cgp.hpp"


// Standard scene environment but replacing the common rotating camera with a camera_head

//  camera_head is a camera model that rotates around its own position - this appropriate to model free-flight.

struct scene_environment_camera_head : cgp::scene_environment_basic_camera_spherical_coords {


	using cgp::scene_environment_basic_camera_spherical_coords::scene_environment_basic_camera_spherical_coords;



	// Standard parameters (same as basic environment)

	cgp::vec3 background_color;

	cgp::camera_projection projection;

	cgp::vec3 light;  // stores the light position


	// Change the standard rotating camera to a "head camera" more appropriate to model free-flight (*)

	cgp::camera_head camera;


	scene_environment_camera_head();




	// Add to the standard scene the ID of the environment map texture

	GLuint environment_map_texture = 0;

};


void opengl_uniform(GLuint shader, scene_environment_camera_head const& environment);

void draw(cgp::mesh_drawable const& drawable, scene_environment_camera_head const& environment);


