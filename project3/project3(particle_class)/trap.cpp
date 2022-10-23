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

    r.set_size(3);
    v.set_size(3);

    r(0) = x(0);
    r(1) = y(0);
    r(2) = z(0);

    v(0) = vx(0);
    v(1) = vy(0);
    v(2) = vz(0);  

    E.set_size(3);
    B.set_size(3);
    F_ext.set_size(3);

    k1r.set_size(3);
    k2r.set_size(3);
    k3r.set_size(3);
    k4r.set_size(3);

    k1v.set_size(3);
    k2r.set_size(3);
    k3r.set_size(3);
    k4r.set_size(3);

    rtemp.set_size(3);
    vtemp.set_size(3);

    kravg.set_size(3);
    kvavg.set_size(3);



}

arma::vec trap::external_E_field(arma::vec r)
{
    E(0) = V0_/pow(d_, 2) * r(0);
    E(1) = V0_/pow(d_, 2) * r(1);
    E(2) = - 2 * V0_/pow(d_, 2) * r(2);

    return E;
}

arma::vec trap::external_B_field()
{
    B(0) = 0;
    B(1) = 0;
    B(2) = B0_;

    return B;
}

arma::vec trap::total_force_external()
{
    F_ext(0) = particles[0].q_ * external_E_field(r)(0) + particles[0].q_ * v(1) * external_B_field()(2);
    F_ext(1) = particles[0].q_ * external_E_field(r)(1) - particles[0].q_ * v(0) * external_B_field()(2);
    F_ext(2) = particles[0].q_ * external_E_field(r)(2);

    return F_ext;
}

void trap::Forward_Euled(double dt)
{
    for(int i = 0; i<n-1; i++)
    {
        x(i+1) = x(i) + dt * vx(i);
        y(i+1) = y(i) + dt * vy(i);
        z(i+1) = z(i) + dt * vz(i);

        vx(i+1) = vx(i) + dt * total_force_external()(0)/particles[0].m_;
        vy(i+1) = vy(i) + dt * total_force_external()(1)/particles[0].m_;
        vz(i+1) = vz(i) + dt * total_force_external()(2)/particles[0].m_;

        r(0) = x(i+1);
        r(1) = y(i+1);
        r(2) = z(i+1);

        v(0) = vx(i+1);
        v(1) = vy(i+1);
        v(2) = vz(i+1); 
    }
}

void trap::RK4(double dt)
{
    for(int i = 0; i<n-1; i++)
    {
        rtemp = r;
        vtemp = v;

        t0 = i * dt;

        k1r = v;
        k1v = total_force_external()/particles[0].m_;
        if(i ==1){break;}

        r = rtemp + k1r * (t0+dt/2);
        v = vtemp + k1v * (t0+dt/2);

        k2r =  v;
        k2v = total_force_external()/particles[0].m_;

        r = rtemp + k2r * (t0+dt/2);
        v = vtemp + k2v * (t0+dt/2);

        k3r = v;
        k3v = total_force_external()/particles[0].m_;

        r = rtemp + k3r * dt;
        v = vtemp + k3v * dt;

        k4r = v;
        k4v = total_force_external()/particles[0].m_;

        kravg = 1./6 * (k1r + 2 * k2r + 2 * k3r + k4r);
        kvavg = 1./6 * (k1v + 2 * k2v + 2 * k3v + k4v);

        r = rtemp + kravg * dt;
        v = vtemp + kvavg * dt;

        x(i+1) = r(0);
        vx(i+1) = v(0);

        y(i+1) = r(1);
        vy(i+1) = v(1);

        z(i+1) = r(2);
        vz(i+1) = v(2);
    }
}