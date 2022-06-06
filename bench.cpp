#include "bench.hpp"

using namespace cgp;

mesh create_bench() {
    return mesh_load_file_obj("assets/HollowBench.obj");
}

void place_bench(mesh_drawable& bench,vec3 position) {
    bench.transform.scaling = 0.0015f; 
    bench.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi / 2);
    bench.transform.translation = { -0.784f,0.103f,0.804f };
    bench.transform.translation = position;

}