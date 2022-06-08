#include "scene.hpp"
#include "bug.hpp"


using namespace cgp;

hierarchy_mesh_drawable create_bug() {
    hierarchy_mesh_drawable bug;

	mesh_drawable body; 
	body.initialize(mesh_primitive_ellipsoid({ 1.0f, 1.0f, 1.5f }), "body");
	body.texture = opengl_load_texture_image("assets/body.png"); // associate a texture-image to each element
	
	mesh_drawable head; 
	head.initialize(mesh_primitive_sphere(0.9f),"head");
	head.texture = opengl_load_texture_image("assets/head.png");

	mesh_drawable wing_L; 
	wing_L.initialize(mesh_load_file_obj("assets/wing.obj"), "wing_L");
	wing_L.texture = opengl_load_texture_image("assets/wing.png");

	mesh_drawable wing_R; 
	wing_R.initialize(mesh_load_file_obj("assets/wing.obj"), "wing_R");
	wing_R.texture = opengl_load_texture_image("assets/wing.png");
	wing_R.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi);

	mesh_drawable eye_L; 
	eye_L.initialize(mesh_primitive_sphere(0.2f), "eye_R");
	eye_L.shading.color = { 0.2f,0.2f,0.2f };

	mesh_drawable eye_R; 
	eye_R.initialize(mesh_primitive_sphere(0.2f), "eye_L");
	eye_R.shading.color = { 0.2f,0.2f,0.2f };

	mesh_drawable butt;
	butt.initialize(mesh_primitive_sphere(0.4f), "butt");
	butt.shading.color = { 0.6f,0.6f,0.6f };

    bug.add(body);
    bug.add(head, "body", { 0,0,1.8 });
    bug.add(eye_R, "head", { 0.4f,0.3f,0.6f });
    bug.add(eye_L, "head", { -0.4f,0.3f,0.6f });
    bug.add(wing_L, "body", { 0,1.03f,0 });
    bug.add(wing_R, "body", { 0,1.03f,0 });
    bug.add(butt, "body", { 0,0,-1.5f });

    return bug;
}

void update_bug(float t,hierarchy_mesh_drawable& bug) {
    bug["body"].transform.translation = { 0,0.2f * std::cos(5 * t),0 };
    bug["wing_L"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 8.0f * (1 + std::cos(20 * t)));
    bug["wing_R"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,-1 }, Pi / 8.0f * (1 + std::cos(20 * t)));
    bug["head"].transform.translation = vec3{ 0,0,1.8 } + vec3{ 0,0,0.1f * std::cos(2.5 * t) };
    bug["head"].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, Pi / 8.0f * std::cos(5 * t));
}

