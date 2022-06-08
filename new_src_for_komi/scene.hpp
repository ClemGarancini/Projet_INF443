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


    //Terrain
    mesh terrain_mesh;
    mesh_drawable terrain_drawable;
    perlin_noise_parameters parameters;


    //Houses
    std::vector<vec3> houses_pos = {vec3{2.7f,0,4},vec3{3.1f,0,-4.3f},vec3{-5.7f,0,3.1f},vec3{-4.1f,0,-7.6f},vec3{6.9f,0,7.5f},
                                    vec3{0,0,6.9f},vec3{-5.1f,0,6.6f},vec3{-5,0,0}};

    std::vector<float> houses_rot = {-3*Pi/4,2*Pi/3,-Pi/6,Pi/3,-3*Pi/4,-Pi/2-Pi/4,0};

    std::vector<hierarchy_mesh_drawable> houses;


    //Road
    std::vector<vec3> points_for_road;
    mesh_drawable_multitexture road_drawable;


    hierarchy_mesh_drawable bug;
    mesh_drawable bench_drawable;






	mesh_drawable lampe;


	light_shape_drawable light_drawable;


	// ****************************** //
	// Functions
	// ****************************** //
	void update_camera();
	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop


};





