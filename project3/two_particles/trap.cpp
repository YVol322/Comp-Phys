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
}

void trap::setsize()
{
    x.set_size(n+1, N);
    y.set_size(n+1, N);
    z.set_size(n+1, N);

    vx.set_size(n+1, N);
    vy.set_size(n+1, N);
    vz.set_size(n+1, N);

    time.set_size(n+1);

    r.set_size(3);
    v.set_size(3);

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

    F_int.set_size(3);
    F_tot.set_size(3);
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

arma::vec trap::force_particle(int i, int j)
{
    double xi_xj = pow(particles[i].r0_(0) - particles[j].r0_(0),2);
    double yi_yj = pow(particles[i].r0_(1) - particles[j].r0_(1),2);
    double zi_zj = pow(particles[i].r0_(2) - particles[j].r0_(2),2);
    double module3 = pow(sqrt(xi_xj + yi_yj + zi_zj), 3);

    F_int = k_e * particles[i].q_ / particles[i].m_ * particles[j].q_ * (particles[i].r0_ - particles[j].r0_)/ module3;

    return F_int;
}

arma::vec trap::total_force_external(int i)
{
    F_ext = particles[i].q_ * (external_E_field(r) + arma::cross(v, external_B_field()));

    return F_ext;
}

arma::vec trap::total_force(int i)
{
    if(i == 0)
    {
        F_tot = total_force_external(i) + force_particle(0, 1);
        
        return F_tot;
    }
    if(i == 1)
    {
        F_tot = total_force_external(i) + force_particle(1, 0);

        return F_tot;
    }
    else
    {
        F_tot.fill(0);

        return F_tot;
    }
}




void trap::Forward_Euled(double dt)
{
        for(int i = 0; i<n; i++)
        {
            for(int j =0; j<N; j++)
            {
                x(i+1, j) = x(i, j) + dt * vx(i, j);
                y(i+1, j) = y(i, j) + dt * vy(i, j);
                z(i+1, j) = z(i, j) + dt * vz(i, j);

                vx(i+1, j) = vx(i, j) + dt * total_force_external(j)(0) / particles[0].m_;
                vy(i+1, j) = vy(i, j) + dt * total_force_external(j)(1) / particles[0].m_;
                vz(i+1, j) = vz(i, j) + dt * total_force_external(j)(2) / particles[0].m_;

                time(i+1) = dt * (i+1);

                if(j ==1)
                {
                    break;
                }

                r(0) = x(i, j+1);
                r(1) = y(i, j+1);
                r(2) = z(i, j+1);

                v(0) = vx(i, j+1);
                v(1) = vy(i, j+1);
                v(2) = vz(i, j+1); 
            }

            r(0) = x(i+1, 0);
            r(1) = y(i+1, 0);
            r(2) = z(i+1, 0);

            v(0) = vx(i+1, 0);
            v(1) = vy(i+1, 0);
            v(2) = vz(i+1, 0); 
        }
}
//
//void trap::RK4(double dt)
//{
//    for(int i = 0; i<n; i++)
//    {
//        rtemp = r;
//        vtemp = v;
//
//        t0 = i * dt;
//
//        k1r = v;
//        k1v = total_force_external()/particles[0].m_;
//
//        r = rtemp + k1r * dt/2;
//        v = vtemp + k1v * dt/2;
//
//        k2r =  v;
//        k2v = total_force_external()/particles[0].m_;
//
//        r = rtemp + k2r * dt/2;
//        v = vtemp + k2v * dt/2;
//
//        k3r = v;
//        k3v = total_force_external()/particles[0].m_;
//
//        r = rtemp + k3r * dt;
//        v = vtemp + k3v * dt;
//
//        k4r = v;
//        k4v = total_force_external()/particles[0].m_;
//
//        kravg = 1./6 * (k1r + 2 * k2r + 2 * k3r + k4r);
//        kvavg = 1./6 * (k1v + 2 * k2v + 2 * k3v + k4v);
//
//        r = rtemp + kravg * dt;
//        v = vtemp + kvavg * dt;
//
//        x(i+1) = r(0);
//        vx(i+1) = v(0);
//
//        y(i+1) = r(1);
//        vy(i+1) = v(1);
//
//        z(i+1) = r(2);
//        vz(i+1) = v(2);
//
//        time(i+1) = dt * (i+1);
//    }
//}