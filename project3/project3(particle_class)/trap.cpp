#include "trap.hpp"

#include<vector>

trap::trap(double B0, double V0, double d)
{
    B0_ = B0;
    V0_ = V0;
    d_ = d;
}

void trap::add_particle(particle particle_input)
{
    particles.push_back(particle_input);

    x.set_size(n);
    y.set_size(n);
    z.set_size(n);

    vx.set_size(n);
    vy.set_size(n);
    vz.set_size(n);

    x(0) = particles[0].r0_(0);
    y(0) = particles[0].r0_(1);
    z(0) = particles[0].r0_(2);

    vx(0) = particles[0].v0_(0);
    vy(0) = particles[0].v0_(1);
    vz(0) = particles[0].v0_(2);

}

arma::vec trap::external_E_field(arma::vec r)
{
    E.set_size(3);

    E(0) = V0_/pow(d_, 2) * r(0);
    E(1) = V0_/pow(d_, 2) * r(1);
    E(2) = - 2 * V0_/pow(d_, 2) * r(2);
    return E;
}

arma::vec trap::external_B_field()
{
    B.set_size(3);
    
    B(0) = 0;
    B(1) = 0;
    B(2) = B0_;
    return B;
}

arma::vec trap::total_force_external()
{
    F_ext.set_size(3);

    F_ext(0) = particles[0].q_ * E(0) + particles[0].q_ * particles[0].v0_(1) * B(2);
    F_ext(1) = particles[0].q_ * E(1) + particles[0].q_ * particles[0].v0_(0) * B(2);
    F_ext(2) = particles[0].q_ * E(2);

    return F_ext;
}