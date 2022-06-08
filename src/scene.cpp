#include "scene.hpp"
#include "home.hpp"
#include "home2.hpp"
#include "road.hpp"
#include "terrain.hpp"
#include "Mesh_drawable_multitexture/mesh_drawable_multitexture.hpp"
#include "bench.hpp"
#include "light.hpp"
#include "bug.hpp"
#include <cmath>

using namespace cgp;

void scene_structure::update_camera() {
	inputs_keyboard_parameters const& keyboard = inputs.keyboard;
	camera_head& camera = environment.camera;
	float dt = timer.update();
	if (keyboard.space) {
		camera.manipulator_translate_in_plane({ 0,-2.5f *dt});
	 }
	if (keyboard.shift) {
		camera.manipulator_translate_in_plane({ 0,2.5 * dt });
	}
	if (keyboard.q) {
		camera.manipulator_translate_in_plane({ 3*dt,0 });
	}
	if (keyboard.e) {
		camera.manipulator_translate_in_plane({ -3 * dt,0 });
	}
	if (keyboard.left) {
		camera.manipulator_rotate_roll_pitch_yaw(0,0,2*dt);
	}
	if (keyboard.right) {
		camera.manipulator_rotate_roll_pitch_yaw(0, 0, -2*dt);
	}
	if (keyboard.up) {
		camera.position_camera += 2*dt*camera.front();
	}
	if (keyboard.down) {
		camera.position_camera -= 2*dt * camera.front();
	}
	if (inputs.mouse.click.left && inputs.keyboard.ctrl) {
		vec2 const& p1 = inputs.mouse.position.current;
		vec2 const& p0 = inputs.mouse.position.previous;
		float d_phi = (p1 - p0).x;
		float d_theta = -(p1 - p0).y;
		if (fabs(d_phi) > fabs(d_theta)) {
			camera.manipulator_rotate_roll_pitch_yaw(0, 0, d_phi);
		}
		else {
			camera.manipulator_rotate_roll_pitch_yaw(0, d_theta, 0);
		}
		
	}
	
}


void scene_structure::initialize()
{

	//skybox.initialize("textures/skybox/", "Skybox");
	// Basic set-up
	// ***************************************** //
    GLuint const shader_lights = opengl_load_shader("shaders/mesh_lights/vert.glsl", "shaders/mesh_lights/frag.glsl");
    mesh_drawable::default_shader = shader_lights;
    environment.background_color = {0,0,0.05f};

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.position_camera = { 2,1,0 };
	

    //Terrain
	terrain_mesh = create_terrain_mesh();
	terrain_drawable.initialize(terrain_mesh, "terrain");
    terrain_drawable.transform.translation = {0,-0.227f,0};
	update_terrain(terrain_mesh, terrain_drawable, parameters);



    // Houses
    house = create_house({0,-0.8f,0},0);
    house2 = create_house_2({0,0,0});

	// ***************************************** //
	// Road

    points_for_road.resize(8);
    points_for_road[0] = vec3{ -4, -0.18f + get_terrain_height(-4,-6,terrain_mesh),-6 };
	points_for_road[1] = vec3{ -3, -0.18f + get_terrain_height(-3,-5,terrain_mesh),-5 };
	points_for_road[2] = vec3{ -0.5f, -0.18f + get_terrain_height(-0.5f,-2,terrain_mesh),-2 };
	points_for_road[3] = vec3{ -2, -0.18f + get_terrain_height(-2,1.5f,terrain_mesh),1.5f };
	points_for_road[4] = vec3{ 0, -0.07f + get_terrain_height(0,3,terrain_mesh),3 };
	points_for_road[5] = vec3{ 4, -0.15f + get_terrain_height(4,-1,terrain_mesh),-1 };
	points_for_road[6] = vec3{ 1, -0.19f + get_terrain_height(1,-5,terrain_mesh),-5 };
    points_for_road[7] = vec3{ 0, -0.19f + get_terrain_height(0,-6,terrain_mesh),-6 };

    mesh road_mesh = create_road_mesh(points_for_road, 15, 0.1f,terrain_mesh);
	road_drawable.initialize(road_mesh, "Road");
    road_drawable.texture = opengl_load_texture_image("textures/Cobblestone.jpg", GL_REPEAT, GL_REPEAT);


    //Lights
    lights_pos.resize(lampes_pos.size());
    for (int i =0; i<lampes_pos.size();i++) {
        vec3 vec = {cos(lampes_rot[i]),0,sin(lampes_rot[i])};
        lights_pos[i] = lampes_pos[i]+0.2f*vec+vec3{0,0.8f,0};
    }
    light_drawable.initialize(shader_lights);
    compute_light_position(lights_pos,environment);


	//Bench
    mesh bench_mesh = create_bench();
    bench.initialize(bench_mesh);
    bench.transform.scaling = 0.0015f;
    bench.transform.rotation = rotation_transform::from_axis_angle({1,0,0},-Pi/2);

    /*
	for (int i = 0; i < 4; i++) {
		mesh bench_mesh = create_bench();
		bench[i].initialize(bench_mesh, "Bench");
		bench[i].transform.scaling = 0.0015f;
		bench[i].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi / 2);
		bench[i].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, Pi / 2);
		bench[i].transform.translation = { -0.784f,0.103f,0.804f };
		//bench_pos[i] += { -1, 0.05f, 0 };
		//bench[i].transform.translation = bench_pos[i];
		//bench[i].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, -bench_rot[i] + Pi / 2);
		bench[i].shading.color = { 0.2f,0.2f,0.25f };
	}
    mesh bench_mesh = create_bench();
    bench_drawable.initialize(bench_mesh,"Bench");
	bench_drawable.transform.scaling = 0.0015f;
	bench_drawable.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi / 2);
	bench_drawable.transform.translation = { -0.784f,0.103f,0.804f };
	bench_drawable.shading.color = { 0.2f,0.2f,0.25f };
	
    place_bench(bench_drawable, { 0,0,0 });*/



	/*test.initialize(mesh_primitive_quadrangle());
	test.texture = opengl_load_texture_image("textures/805197.jpg", GL_REPEAT, GL_REPEAT);*/

	//lights


    //light_drawable.initialize(shader_lights);
    mesh lampe_mesh = create_support();
    lampe.initialize(lampe_mesh);


    //bug = create_bug();
}




void scene_structure::display()
{


    environment.light = environment.camera.position();
   // timer.update();
    //float t = timer.t;
    //compute_light_position(t, environment);
    //update_bug(t,bug);

    //Terrain
    draw(terrain_drawable, environment);


    //Houses
	for (int i = 0; i < 5; i++) {
        house["House"].transform.rotation = rotation_transform::from_axis_angle({0,1,0},-houses_rot[i]);
        house["House"].transform.translation = houses_pos[i];
        house.update_local_to_global_coordinates();
        draw(house, environment);
	}
    for (int i =0; i<5;i++) {
        house2["House"].transform.rotation = rotation_transform::from_axis_angle({0,1,0},-houses2_rot[i]);
        house2["House"].transform.translation = houses2_pos[i];
        house2.update_local_to_global_coordinates();
        draw(house2, environment);
    }



    //lamp
    for (int i = 0; i<6;i++) {
        lampe.transform.translation = lampes_pos[i];
        lampe.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, -lampes_rot[i]);
        draw(lampe,environment);
    }

    //Road
    draw(road_drawable, environment);


	//bench

//	for (int i = 0; i < 4; i++) {
//        bench.transform.translation = bench_pos[i];
//        bench.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, -bench_rot[i] + Pi / 2);
//        draw(bench, environment);
//	}


    draw(light_drawable, environment);

	if (gui.display_wireframe) {

		draw_wireframe(terrain_drawable, environment);
        draw_wireframe(bench_drawable,environment);
	}
    if (gui.display_frame) {
        draw(global_frame,environment);
    }



	//draw(test, environment);
	
	
	
	//bool update = false;
	//update |= ImGui::SliderFloat("Persistance", &parameters.persistency, 0.1f, 0.6f);
	//update |= ImGui::SliderFloat("Frequency gain", &parameters.frequency_gain, 1.5f, 2.5f);
	//update |= ImGui::SliderInt("Octave", &parameters.octave, 1, 8);
	//update |= ImGui::SliderFloat("Height", &parameters.terrain_height, 0.1f, 1.5f);

	//if (update)// if any slider has been changed - then update the terrain
	//	update_terrain(terrain_mesh, terrain_drawable, parameters);

}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);
    ImGui::Checkbox("Frame",&gui.display_frame);
    //ImGui::SliderFloat("x",&terrain_drawable.transform.translation.y,-1.0f,1.0f);

}


