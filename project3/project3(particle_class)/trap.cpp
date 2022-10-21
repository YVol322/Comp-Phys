#include "trap.hpp"

trap::trap(double B0, double V0, double d, std::vector<particle> particle_parameters)
{
    B0_ = B0;
    V0_ = V0;
    d_ = d;
    particle_parameters_ = particle_parameters;
}