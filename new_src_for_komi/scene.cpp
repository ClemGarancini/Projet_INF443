#include "scene.hpp"
#include "home.hpp"
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



	// House
	// ***************************************** //
    houses.resize(3);
    for (int i = 0;i<3;i++){
        vec3 pos = houses_pos[i]/2;
        float z = get_terrain_height( pos.x,pos.z,terrain_mesh);
        pos += {0,z,0};
        houses[i] = create_house({0,0,0},0);
        houses[i]["House"].transform.rotation = rotation_transform::from_axis_angle({0,1,0},-houses_rot[i]);
        houses[i]["House"].transform.translation = pos;
    }


	// Road
	// ***************************************** //
    points_for_road.resize(9);
    for (int i = 0;i<9;i++) {
        float x = cos(i*Pi/3);
        float y = sin(i*Pi/3);
        float z = get_terrain_height( x,y,terrain_mesh);
        points_for_road[i] = vec3{x,z-0.227f,y};
    }
    mesh road_mesh = create_road_mesh(points_for_road, 15, 0.1f,terrain_mesh);
	road_drawable.initialize(road_mesh, "Road");
    road_drawable.texture = opengl_load_texture_image("textures/Cobblestone.jpg", GL_REPEAT, GL_REPEAT);
//	GLuint const shader = opengl_load_shader("shaders/multitexture/vert.glsl", "shaders/multitexture/frag.glsl");
//	road_drawable.shader = shader;


	//Bench

    mesh bench_mesh = create_bench();
    bench_drawable.initialize(bench_mesh,"Bench");
	bench_drawable.transform.scaling = 0.0015f;
	bench_drawable.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi / 2);
	bench_drawable.transform.translation = { -0.784f,0.103f,0.804f };
	bench_drawable.shading.color = { 0.2f,0.2f,0.25f };
	
	//place_bench(bench_drawable, { 0,0,0 });

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
    for (int i = 0;i< 3;i++) {
        houses[i].update_local_to_global_coordinates();
        draw(houses[i], environment);
    }


    //Road
    draw(road_drawable, environment);
    //draw(bench_drawable,environment);
    //draw(lampe, environment);
    //draw(light_drawable, environment);

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


