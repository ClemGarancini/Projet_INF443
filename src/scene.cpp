#include "scene.hpp"
#include "home.hpp"
#include "road.hpp"
#include "terrain.hpp"
#include "Mesh_drawable_multitexture/mesh_drawable_multitexture.hpp"
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
	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.position_camera = { 2,1,0 };
	
	terrain_mesh = create_terrain_mesh();
	terrain_drawable.initialize(terrain_mesh, "terrain");
	update_terrain(terrain_mesh, terrain_drawable, parameters);

	//plane.initialize(mesh_primitive_quadrangle({ -20,0,-20 }, { 20,0,-20 },{20,0,20},{-20,0,20}), "Plane");

	// House
	// ***************************************** //

	house = create_house(vec3{5,0.35f,0});

	// Road
	// ***************************************** //
	mesh road_mesh = create_road_mesh(std::vector<vec3>{ vec3{ -1,0,-1 }, vec3{ 0,0,0 }, vec3{ 1,0,1 }, vec3{ 1,0,2 }, vec3{ 2,0,2 }, vec3{ 3,0,3 }}, 15, 0.1f);
	road_drawable.initialize(road_mesh, "Road");
	road_drawable.texture = opengl_load_texture_image("textures/Cobblestone.jpg", GL_REPEAT, GL_REPEAT);
	GLuint const shader = opengl_load_shader("shaders/multitexture/vert.glsl", "shaders/multitexture/frag.glsl");
	road_drawable.shader = shader;
	/*test.initialize(mesh_primitive_quadrangle());
	test.texture = opengl_load_texture_image("textures/805197.jpg", GL_REPEAT, GL_REPEAT);*/
}




void scene_structure::display()
{

	// Basic elements of the scene
	environment.light = environment.camera.position();


	timer.update();

	draw(plane, environment);
	//std::cout << "before" << std::endl;
	house.update_local_to_global_coordinates();

	draw(house, environment);
	draw(terrain_drawable, environment);
	draw(road_drawable, environment);

	if (gui.display_wireframe) {
		draw_wireframe(plane, environment);
		draw_wireframe(house, environment);
		draw_wireframe(terrain_drawable, environment);
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
}


