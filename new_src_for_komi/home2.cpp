#include "home2.hpp"
#include "math.h"

using namespace cgp;


hierarchy_mesh_drawable create_house_2(vec3 center) {
	hierarchy_mesh_drawable house;

    mesh walls_mesh = create_walls_2(center);
	mesh_drawable walls_drawable;
	walls_drawable.initialize(walls_mesh, "House"); walls_drawable.anisotropic_scale = { 1,2,0.5f }; walls_drawable.transform.translation = center;
    walls_drawable.texture = opengl_load_texture_image("textures/CityStreetAsphaltGenericCracked002_Flat.jpg", GL_REPEAT, GL_REPEAT);
	house.add(walls_drawable);

    mesh door_mesh = create_door_2(0.3f, 0.02f);
	mesh_drawable door_drawable;
	door_drawable.initialize(door_mesh, "Door"); door_drawable.anisotropic_scale = { 0.4f,1.0f,1.0f }; door_drawable.transform.rotation = rotation_transform::from_axis_angle({0,1,0},Pi/2);
    door_drawable.texture = opengl_load_texture_image("textures/CityStreetAsphaltGenericCracked002_Flat.jpg", GL_REPEAT, GL_REPEAT);
	house.add(door_drawable,"House",center + vec3{1,-0.3f,0});

//    mesh door_for_texture_mesh = create_door_for_texture(0.3f,0.4f);
//    mesh_drawable door_for_texture_drawable;
//    door_for_texture_drawable.initialize(door_for_texture_mesh); door_for_texture_drawable.anisotropic_scale = {1.0f,1.0f,0.4f}; //door_for_texture_drawable.transform.rotation = rotation_transform::from_axis_angle({0,1,0},Pi/2);
//    GLuint const shader_with_transparency = opengl_load_shader("shaders/transparency/vert.glsl","shaders/transparency/frag.glsl");
//    door_for_texture_drawable.shader = shader_with_transparency;
//    door_for_texture_drawable.shading.phong = { 0.4f, 0.6f, 0, 1 };
//    door_for_texture_drawable.texture = opengl_load_texture_image("textures/hollow-knight-mask-maker-pack.png", GL_REPEAT, GL_REPEAT);
//    house.add(door_for_texture_drawable,"House",center + vec3{1.01f,-0.05f,0});


	std::vector<mesh_drawable> windows_drawable;
	windows_drawable.resize(9);
	for (int i = 0;i < 4;i++) {
        mesh window_mesh = create_egg_window_2();
		
		std::string name = "Window ";
		name += std::to_string(i);
        windows_drawable[i].initialize(window_mesh, name); windows_drawable[i].anisotropic_scale = { 0.6f,1,0.7f }; windows_drawable[i].transform.translation = vec3{ 0, 0.3f + .4f * i , 0.5f * sqrt(1 - (.15f + .2f * i) * (.15f + .2f * i)) } + center;
        windows_drawable[i].transform.rotation = rotation_transform::from_axis_angle({0,1,0},Pi/2);
        windows_drawable[i].texture = opengl_load_texture_image("textures/Windows_1.jpg", GL_REPEAT, GL_REPEAT);
		house.add(windows_drawable[i], "House");

		std::string name2 = name + std::to_string(i+4);
		windows_drawable[i+4].initialize(window_mesh, name2); windows_drawable[i+4].anisotropic_scale = { 0.6f,1,0.7f }; windows_drawable[i+4].transform.translation = vec3{ 0, 0.3f + .4f * i , -0.5f * sqrt(1 - (.15f + .2f * i) * (.15f + .2f * i)) } + center;
        windows_drawable[i+4].transform.rotation = rotation_transform::from_axis_angle({0,1,0},Pi/2);
        windows_drawable[i+4].texture = opengl_load_texture_image("textures/Windows_1.jpg", GL_REPEAT, GL_REPEAT);
        house.add(windows_drawable[i+4], "House");
	}
    mesh window_mesh = create_egg_window_2();
	windows_drawable[8].initialize(window_mesh, "Window 8"); windows_drawable[8].anisotropic_scale = { 0.6f,1,0.7f }; windows_drawable[8].transform.translation = vec3{ 1, 0.3f, 0 } + center;
	windows_drawable[8].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, Pi);
	windows_drawable[8].texture = opengl_load_texture_image("textures/Windows_1.jpg", GL_REPEAT, GL_REPEAT);
	house.add(windows_drawable[8], "House");



	return house;
}


mesh create_walls_2(vec3 center) {
	return mesh_primitive_sphere(1,center);
}

mesh create_door_2(float ray_maj,float ray_min)  {
	mesh door = mesh_primitive_torus(ray_maj, ray_min);
	door.push_back(mesh_primitive_cylinder(ray_maj+0.015f, { 0,0,0 }, { 0,0,-0.2f }, 10,20,true));
	return door;
}

mesh create_door_for_texture_2(float ray_maj, float scale_z) {
    mesh door;

    door.position.resize(41);
    door.uv.resize(41);
    for (int i = 0;i<40;i++) {
        float y_curr = ray_maj*sin(i*Pi/39);
        float z_curr = ray_maj*cos(i*Pi/39);
        door.position[i] = {0,y_curr,z_curr};

        float u = 0.5f + z_curr*scale_z;
        float v = 1-y_curr/ray_maj;
        door.uv[i] = {u,v};
    }
    door.position[40] = {0,0,0};
    door.uv[40]= {0.5f,1};

    door.connectivity.resize(39);
    for (int i =0;i<39;i++) {
        door.connectivity[i] = {i,i+1,40};
    }
    door.fill_empty_field();
    return door;
}

mesh create_pediment_2(vec3 center)	 {
	float a_max = 1.15f;
	float a_min = 0.95f;
	float b = 0.79f;
	float x_max = 0.9f;
    float z_max = 0.042f;;
    float y_min = b * sqrt(1 - (x_max * x_max) / (a_min * a_min));
    float y_max = b * sqrt(1 - (x_max * x_max) / (a_max * a_max));

	mesh pediment;
	pediment.position.resize(42);
    pediment.uv.resize(42);
    pediment.position[41] = vec3{ x_max,y_min ,0 } + center;
    pediment.uv[41] = {0.5f,1};
	for (int i = 0; i < 21;i++) {
		float t = fabs(i - 20) / 20;
		float a_curr = (1 - t) * a_max + t * a_min;
		float y_curr = b * sqrt(1 - (x_max * x_max) / (a_curr * a_curr));
		float z_curr = sqrt(t) * z_max;
		if (i < 20) {
			pediment.position[i] = vec3{ x_max,y_curr,z_curr } + center;
			pediment.position[40 - i] = vec3{ x_max,y_curr,-z_curr } + center;
		}
		else pediment.position[i] = vec3{ x_max,y_curr,z_curr } + center;


        float u_rel = static_cast<float>(z_curr)/(4*static_cast<float>(z_max));
        float v = static_cast<float>(y_max-y_curr)/static_cast<float>(y_max-y_min);

        if (i<20) {
            pediment.uv[i] = {0.5f+u_rel,v};
            pediment.uv[40-i] = {0.5f-u_rel,v};
        }
        else pediment.uv[i] = {0.5f,0};
	}

	pediment.connectivity.resize(40);
	for (int i = 0; i < 40;i++) {
		pediment.connectivity[i] = { i,41,i + 1 };
	}




	pediment.fill_empty_field();
	return pediment;
}

mesh create_roof_2(vec3 center) {
	float a_max = 1.15f;
	float a_min = 0.95f;
	float b = 0.79f;
	float x_max = 0.9f;
    float z_max = 0.042f;



	mesh roof;
	roof.position.resize(4100);
	for (int i = 0;i < 21;i++) {
		for (int j = 0; j < 100;j++) {
			float t = fabs(i - 20) / 20;
			float a_curr = (1 - t) * a_max + t * a_min;
			float x_curr = j * x_max / 99;
			float y_curr = b * sqrt(1 - (x_curr * x_curr) / (a_curr * a_curr));
			float z_curr = sqrt(t) * z_max;
			if (i < 20) {
				roof.position[100 * i + j] = vec3{ x_curr,y_curr,z_curr } + center;
				roof.position[100 * (40-i) + j] = vec3{ x_curr,y_curr,-z_curr } + center;
			}
			else roof.position[100 * i + j] = vec3{ x_curr,y_curr,z_curr } + center;
		}
	}

	roof.connectivity.resize(7920);
	for (int i = 0;i < 40;i++) {
		for (int j = 0; j < 99;j++) {
			roof.connectivity[2 * (99 * i + j)] = { 100 * i + j,100 * (i + 1) + j,100 * (i + 1) + j + 1 };
			roof.connectivity[2 * (99 * i + j) + 1] = { 100 * i + j,100 * (i + 1) + j + 1,100 * i + j + 1 };
		}
	}

	roof.uv.resize(4100);
	for (int i = 0;i < 41;i++) {
		for (int j = 0; j < 100;j++) {
			float u = static_cast<float>(i) / static_cast<float>(40);
			float v = static_cast<float>(j) / static_cast<float>(100);
			roof.uv[100 * i + j] = { u,v };
		}
	}

	roof.fill_empty_field();
	return roof;
}

mesh create_egg_window_2() {
	return mesh_primitive_sphere(0.1f);
}
