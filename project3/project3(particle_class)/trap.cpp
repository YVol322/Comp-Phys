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

arma::vec trap::external_E_field(arma::vec r)
{
    E.set_size(3);

    E(0) = V0_in/pow(d_in, 2) * r(0);
    E(1) = V0_in/pow(d_in, 2) * r(1);
    E(2) = - 2 * V0_in/pow(d_in, 2) * r(2);
    return E;
}

arma::vec trap::external_B_field()
{
    B.set_size(3);
    
    B(0) = 0;
    B(1) = 0;
    B(2) = B0_in;
    return B;
}

arma::vec trap::total_force_external()
{
    F_ext.set_size(3);

    F_ext(0) = particles[0].q_ * E(0) + particles[0].q_ * particles[0].v_(1) * B(2);
    F_ext(1) = particles[0].q_ * E(1) + particles[0].q_ * particles[0].v_(0) * B(2);
    F_ext(2) = particles[0].q_ * E(2);

    return F_ext;
}