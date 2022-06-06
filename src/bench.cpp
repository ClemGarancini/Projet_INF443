#include "bench.hpp"

using namespace cgp;

mesh create_bench() {
    return mesh_load_file_obj("assets/HollowBench.obj");
}
