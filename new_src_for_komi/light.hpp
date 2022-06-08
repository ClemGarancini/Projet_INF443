#pragma once
#include "cgp/cgp.hpp"
#include "multiple_lights/multiple_lights.hpp"

using namespace cgp;

//hierarchy_mesh_drawable create_light(vec3 position);

mesh create_support();
void compute_light(vec3 position, scene_environment_with_multiple_lights& environment);