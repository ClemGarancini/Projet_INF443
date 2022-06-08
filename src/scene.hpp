#pragma once

#include "cgp/cgp.hpp"
#include "environment_camera_head.hpp"
#include "terrain.hpp"
#include "Mesh_drawable_multitexture/mesh_drawable_multitexture.hpp"
#include "multiple_lights/multiple_lights.hpp"

using namespace cgp;

// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_wireframe  = false;
    bool display_frame = false;
};



// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	cgp::mesh_drawable global_frame;          // The standard global frame
	scene_environment_with_multiple_lights environment; // Standard environment controler
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)

	gui_parameters gui;                       // Standard GUI element storage
	
	cgp::timer_basic timer;

	//Road
	std::vector<vec3> points_for_road;
	mesh_drawable_multitexture road_drawable;

    //Terrain
    mesh terrain_mesh;
    mesh_drawable terrain_drawable;
    perlin_noise_parameters parameters;


    //Houses
	std::vector<vec3> houses_pos = { vec3{4.f, 1, -3.8f}, vec3{1.5f, 1, 3.7},  vec3{0, 1, -4}, vec3{0.5f, 1, 0}, vec3{-2, 1, -2}, vec3{-3, 1, -3}, vec3{-2.5, 1, 4} };

    std::vector<float> houses_rot = {2.6f, 4.f, 2.8f, 3.4f, 5.7f, 5.7f, 5.5f};

    hierarchy_mesh_drawable house;

	std::vector<vec3> houses2_pos = { vec3{4, 0.4f, 2}, vec3{3.5f, 0.4f, 4},  vec3{1.2, 0.4f, -2}, vec3{-3, 0.4f, 0}, vec3{-3.5, 0.4f, 3}};

	std::vector<float> houses2_rot = { 4, 4, 3.14f, 0, 5.5f};

    hierarchy_mesh_drawable house2;

	//lamp
    mesh_drawable lampe;
    std::vector<vec3> lampes_pos = { vec3{4, 0, 0}, vec3{-1, 0, 3.5f}, vec3{-1.5f, 0, -1}, vec3{1.5f, 0, 1.5f}, vec3{2.5f, 0, -4}, vec3{-1.5f, 0, -4} };
    std::vector<float> lampes_rot = {4, 5, 0.5f, 0.75f, 2.3f, 2.3f};

    std::vector<vec3> lights_pos;
    light_shape_drawable light_drawable;

	//bench
    mesh_drawable bench;
	std::vector<vec3> bench_pos = { vec3{4.2, 0, -0.5}, vec3{-0.5, 0, 3.5}, vec3{-1.1, 0, -0.8}, vec3{1.8, 0, 1.2} };
	std::vector<float> bench_rot = { 0, 0, 0, 0 };

	//bug

    hierarchy_mesh_drawable bug;
    mesh_drawable bench_drawable;



	// ****************************** //
	// Functions
	// ****************************** //
	void update_camera();
	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop


};





