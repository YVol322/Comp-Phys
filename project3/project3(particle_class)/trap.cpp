#include "trap.hpp"

#include<vector>

trap::trap(double B0, double V0, double d)
{
    B0_in = B0;
    V0_in = V0;
    d_in = d;
}

void trap::add_particle(particle particle_input)
{
    particles.push_back(particle_input);
}
