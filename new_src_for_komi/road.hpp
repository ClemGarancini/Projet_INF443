#pragma once

#include "cgp/cgp.hpp"

using namespace cgp;

mesh create_road_mesh(std::vector<vec3> points, int N_samples_per_point, float offset,mesh terrain);

