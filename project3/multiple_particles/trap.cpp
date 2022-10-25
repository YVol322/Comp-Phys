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

    r.set_size(3, N);
    v.set_size(3, N);

    E.set_size(3);
    B.set_size(3);
    F_ext.set_size(3);

    k1r.set_size(3, N);
    k2r.set_size(3, N);
    k3r.set_size(3, N);
    k4r.set_size(3, N);

    k1v.set_size(3, N);
    k2v.set_size(3, N);
    k3v.set_size(3, N);
    k4v.set_size(3, N);

    rtemp.set_size(3, N);
    vtemp.set_size(3, N);

    kravg.set_size(3, N);
    kvavg.set_size(3, N);

    F_int.set_size(3);
    F_tot.set_size(3);
}

arma::vec trap::external_E_field(arma::vec r)
{
    double norm = sqrt(pow(r(0),2)+ pow(r(1),2) + pow(r(2),2));
    if(norm > d_)
    {
        E.fill(0);

        return E;
    }
    else
    {
        E(0) = V0_/pow(d_, 2) * r(0);
        E(1) = V0_/pow(d_, 2) * r(1);
        E(2) = - 2 * V0_/pow(d_, 2) * r(2);

        return E;
    }
}

arma::vec trap::external_B_field(arma::vec r)
{
    double norm = sqrt(pow(r(0),2)+ pow(r(1),2) + pow(r(2),2));
    if(norm > d_)
    {
        B.fill(0);

        return B;
    }
    else
    {
        B(0) = 0;
        B(1) = 0;
        B(2) = B0_;

        return B;
    }
}

arma::vec trap::force_particle(int i, int j)
{
    double xi_xj = pow(r(0, i) - r(0, j),2);
    double yi_yj = pow(r(1, i) - r(1, j),2);
    double zi_zj = pow(r(2, i) - r(2, j),2);
    double module3 = pow(sqrt(xi_xj + yi_yj + zi_zj), 3);

    F_int = k_e * particles[i].q_ / particles[i].m_ * particles[j].q_ * (r.col(i) - r.col(j))/ module3;

    return F_int;
}

arma::vec trap::total_force_external(int i)
{
    F_ext = particles[i].q_ * (external_E_field(r.col(i)) + arma::cross(v.col(i), external_B_field(r.col(i))));

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

                vx(i+1, j) = vx(i, j) + dt * total_force(j)(0) / particles[0].m_;
                vy(i+1, j) = vy(i, j) + dt * total_force(j)(1) / particles[0].m_;
                vz(i+1, j) = vz(i, j) + dt * total_force(j)(2) / particles[0].m_;

                time(i+1) = dt * (i+1);
            }

            r(0, 0) = x(i+1, 0);
            r(1, 0) = y(i+1, 0);
            r(2, 0) = z(i+1, 0);

            v(0, 0) = vx(i+1, 0);
            v(1, 0) = vy(i+1, 0);
            v(2, 0) = vz(i+1, 0);

            r(0, 1) = x(i+1, 1);
            r(1, 1) = y(i+1, 1);
            r(2, 1) = z(i+1, 1);

            v(0, 1) = vx(i+1, 1);
            v(1, 1) = vy(i+1, 1);
            v(2, 1) = vz(i+1, 1);

            std::cout << total_force(0) << std::endl;
        }
}

void trap::RK4(double dt)
{
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<N;j++)
        {
            rtemp = r.col(j);
            vtemp = v.col(j);

            t0 = i * dt;

            k1r.col(j) = v.col(j);
            k1v.col(j) = total_force(j)/particles[0].m_;

            r.col(j) = rtemp + k1r.col(j) * dt/2;
            v.col(j) = vtemp + k1v.col(j) * dt/2;

            k2r.col(j) =  v.col(j);
            k2v.col(j) = total_force(j)/particles[0].m_;

            r.col(j) = rtemp + k2r.col(j) * dt/2;
            v.col(j) = vtemp + k2v.col(j) * dt/2;

            k3r.col(j) = v.col(j);
            k3v.col(j) = total_force(j)/particles[0].m_;

            r.col(j) = rtemp + k3r.col(j) * dt;
            v.col(j) = vtemp + k3v.col(j) * dt;

            k4r.col(j) = v.col(j);
            k4v.col(j) = total_force(j)/particles[0].m_;

            kravg.col(j) = 1./6 * (k1r.col(j) + 2 * k2r.col(j) + 2 * k3r.col(j) + k4r.col(j));
            kvavg.col(j) = 1./6 * (k1v.col(j) + 2 * k2v.col(j) + 2 * k3v.col(j) + k4v.col(j));

            r.col(j) = rtemp + kravg.col(j) * dt;
            v.col(j) = vtemp + kvavg.col(j) * dt;


            x(i+1, j) = r(0, j);
            vx(i+1, j) = v(0, j);

            y(i+1, j) = r(1,j);
            vy(i+1, j) = v(1,j);

            z(i+1, j) = r(2, j);
            vz(i+1, j) = v(2, j);

            time(i+1) = dt * (i+1);
        }
    }   
}