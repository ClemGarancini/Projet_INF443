#include "home.hpp"

using namespace cgp;


hierarchy_mesh_drawable create_house(vec3 center) {
	hierarchy_mesh_drawable house;

	mesh walls_mesh = create_walls();
	mesh_drawable walls_drawable;
	walls_drawable.initialize(walls_mesh, "House"); walls_drawable.anisotropic_scale = { 1,0.8f,0.5f }; walls_drawable.transform.translation = center;
	walls_drawable.texture = opengl_load_texture_image("textures/CityStreetAsphaltGenericCracked002_Flat.jpg", GL_REPEAT, GL_REPEAT);
	house.add(walls_drawable);

	mesh door_mesh = create_door(0.3f, 0.02f);
	mesh_drawable door_drawable;
	door_drawable.initialize(door_mesh, "Door"); door_drawable.anisotropic_scale = { 0.4f,1.0f,1.0f }; door_drawable.transform.rotation = rotation_transform::from_axis_angle({0,1,0},Pi/2);
	door_drawable.texture = opengl_load_texture_image("textures/CityStreetAsphaltGenericCracked002_Flat.jpg", GL_REPEAT, GL_REPEAT);
	house.add(door_drawable,"House",center + vec3{1,-0.05f,0});

	mesh roof_mesh = create_roof(center);
	mesh_drawable roof_drawable;
	roof_drawable.initialize(roof_mesh, "Roof");
	roof_drawable.texture = opengl_load_texture_image("textures/CityStreetAsphaltGenericCracked002_Flat.jpg", GL_REPEAT, GL_REPEAT);
	house.add(roof_drawable, "House");

	mesh pediment_mesh = create_pediment(center);
	mesh_drawable pediment_drawable;
	pediment_drawable.initialize(pediment_mesh, "Pediment");
	house.add(pediment_drawable, "Roof");

	std::vector<mesh_drawable> windows_drawable;
	windows_drawable.resize(6);
	for (int i = 0;i < 3;i++) {
		mesh window_mesh = create_egg_window();
		
		std::string name = "Window ";
		name += std::to_string(i);
		windows_drawable[i].initialize(window_mesh, name); windows_drawable[i].anisotropic_scale = { 0.7f,1,0.6f }; windows_drawable[i].transform.translation = vec3{ -.5f + .5f * i , 0.3f , 0.5f*sqrt(1-( - .5f + .5f * i)*(-.5f + .5f * i)-(0.3f/0.8f)* (0.3f / 0.8f)) } + center;
		windows_drawable[i].texture = opengl_load_texture_image("textures/WoodPlanks028_AO_4K.jpg", GL_REPEAT, GL_REPEAT);
		house.add(windows_drawable[i], "House");

		std::string name2 = name + std::to_string(i+3);
		windows_drawable[i+3].initialize(window_mesh, name2); windows_drawable[i+3].anisotropic_scale = { 0.7f,1,0.6f }; windows_drawable[i+3].transform.translation = vec3{ -.5f + .5f * i,0.3f,-0.5f * sqrt(1 - (-.5f + .5f * i) * (-.5f + .5f * i) - (0.3f / 0.8f) * (0.3f / 0.8f)) } + center;
		house.add(windows_drawable[i+3], "House");
	}


	return house;
}


mesh create_walls(vec3 center) {
	return mesh_primitive_sphere(1,center);
}

mesh create_door(float ray_maj,float ray_min)  {
	mesh door = mesh_primitive_torus(ray_maj, ray_min);
	door.push_back(mesh_primitive_cylinder(ray_maj+0.015f, { 0,0,0 }, { 0,0,-0.2f }, 10,20,true));
	return door;
}

mesh create_pediment(vec3 center) {
	float a_max = 1.15f;
	float a_min = 0.95f;
	float b = 0.79f;
	float x_max = 0.9f;
	float z_max = 0.05f;;

	mesh pediment;
	pediment.position.resize(42);
	pediment.position[41] = vec3{ x_max,b * sqrt(1 - (x_max * x_max) / (a_min * a_min)) ,0 } + center;
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
	}

	pediment.connectivity.resize(40);
	for (int i = 0; i < 40;i++) {
		pediment.connectivity[i] = { i,41,i + 1 };
	}
	pediment.fill_empty_field();
	return pediment;
}

mesh create_roof(vec3 center) {
	float a_max = 1.15f;
	float a_min = 0.95f;
	float b = 0.79f;
	float x_max = 0.9f;
	float z_max = 0.05f;



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

mesh create_egg_window() {
	return mesh_primitive_sphere(0.1f);
}