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

int trap::size()
{
    return particles.size();
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
