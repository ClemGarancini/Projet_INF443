#pragma once

#include "cgp/cgp.hpp"
using namespace cgp;


hierarchy_mesh_drawable create_house_2(vec3 center);

mesh create_walls_2( vec3 center = {0,0,0});
mesh create_door_2(float ray_maj, float ray_min);
mesh create_door_for_texture_2(float ray_maj,float scale_z);
mesh create_roof_2(vec3 center);
mesh create_pediment_2(vec3 center);
mesh create_egg_window_2();




