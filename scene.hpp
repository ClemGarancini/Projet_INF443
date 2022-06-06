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
	cgp::mesh_drawable plane;
	hierarchy_mesh_drawable house;
    mesh_drawable bench_drawable;


	mesh terrain_mesh;
	skybox_drawable skybox;

	mesh_drawable terrain_drawable;
	mesh_drawable_multitexture road_drawable;
	mesh_drawable lampe;
	perlin_noise_parameters parameters;
	mesh_drawable test;

	light_shape_drawable light_drawable;


	// ****************************** //
	// Functions
	// ****************************** //
	void update_camera();
	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop


};





