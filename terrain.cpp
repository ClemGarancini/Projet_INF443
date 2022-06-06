
#include "terrain.hpp"

using namespace cgp;

mesh create_terrain_mesh()
{
	int const terrain_sample = 180;
	mesh terrain = mesh_primitive_grid({ -10,0,-10 }, { 10,0,-10 }, { 10,0,10 }, { -10,0,10 },terrain_sample,terrain_sample);
	return terrain;
}

void update_terrain(mesh& terrain, mesh_drawable& terrain_visual, perlin_noise_parameters const& parameters)
{
	// Number of samples in each direction (assuming a square grid)
	int const N = std::sqrt(terrain.position.size());

	// Recompute the new vertices
	for (int ku = 0; ku < N; ++ku) {
		for (int kv = 0; kv < N; ++kv) {
			
			// Compute local parametric coordinates (u,v) \in [0,1]
            const float u = ku/(N-1.0f);
            const float v = kv/(N-1.0f);

			int const idx = ku*N+kv;

			// Compute the Perlin noise
			float const noise = noise_perlin({u, v}, parameters.octave, parameters.persistency, parameters.frequency_gain);

			// use the noise as height value
			terrain.position[idx].y = parameters.terrain_height*noise;

			// use also the noise as color value
			terrain.color[idx] = 0.3f*normalize(vec3(54,69,79))+0.7f*noise*vec3(1,1,1);
		}
	}

	// Update the normal of the mesh structure
	terrain.compute_normal();
	
	// Update step: Allows to update a mesh_drawable without creating a new one
	terrain_visual.update_position(terrain.position);
	terrain_visual.update_normal(terrain.normal);
	terrain_visual.update_color(terrain.color);
	
}

