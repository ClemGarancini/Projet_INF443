#pragma once

#include "cgp/cgp.hpp"
using namespace cgp;


hierarchy_mesh_drawable create_house(vec3 center);

mesh create_walls( vec3 center = {0,0,0});
mesh create_door(float ray_maj, float ray_min);
mesh create_door_for_texture(float ray_maj,float scale_z);
mesh create_roof(vec3 center);
mesh create_pediment(vec3 center);
mesh create_egg_window();




