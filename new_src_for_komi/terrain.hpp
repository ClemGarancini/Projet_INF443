#pragma once

#include "cgp/cgp.hpp"

struct perlin_noise_parameters
{
	float persistency = 0.5f;
	float frequency_gain = 2.25f;
	int octave = 6;
	float terrain_height = 0.29f;
};

float get_terrain_height(float x, float y,cgp::mesh terrain);

// Initialize the mesh of the terrain
cgp::mesh create_terrain_mesh();

// Recompute the vertices of the terrain everytime a parameter is modified
//  and update the mesh_drawable accordingly
void update_terrain(cgp::mesh& terrain, cgp::mesh_drawable& terrain_visual, perlin_noise_parameters const& parameters);
