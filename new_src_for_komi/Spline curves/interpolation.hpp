#pragma once


#include "cgp/cgp.hpp"

using namespace cgp;

// Compute the interpolated position p(t) given a time t and the set of key_positions and key_frame
cgp::vec3 interpolation(float t,float k, cgp::buffer<cgp::vec3> const& key_positions, cgp::buffer<float> const& key_times);
cgp::vec3 cardinal_spline_interpolation(float t, float t0, float t1, float t2, float t3, vec3 const& p0, vec3 const& p1, vec3 const& p2, vec3 const& p3, float K);

