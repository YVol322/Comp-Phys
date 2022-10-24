#include <iostream>
#include <armadillo>
#include <vector>
#include <fstream>
#include "trap.hpp"
#include "trap.cpp"

int main()
{
    double q = 1;
    double m = 40.078;

    arma::vec r1(3);
    r1(0) = 20;
    r1(1) = 0;
    r1(2) = 20;

    arma::vec v1(3);
    v1(0) = 0;
    v1(1) = 25;
    v1(2) = 0;

    arma::vec r2(3);
    r2(0) = 25;
    r2(1) = 25;
    r2(2) = 0;

    arma::vec v2(3);
    v2(0) = 0;
    v2(1) = 40;
    v2(2) = 5;

    double B = 96.5;
    double V = 2.41 * pow(10, 6);
    double d = 500;

    particle p1 = particle(q, m, r1, v1);
    particle p2 = particle(q, m, r2, v2);

    trap t = trap(B, V, d);

    t.n = 16000;
    t.t = 50;
    t.dt = t.t/t.n;
    t.N = 2;

    t.k_e = 1.38935333 * pow(10, 5);

    t.add_particle(p1);
    t.add_particle(p2);

    t.setsize();

    t.x(0, 0) = t.particles[0].r0_(0);
    t.y(0, 0) = t.particles[0].r0_(1);
    t.z(0, 0) = t.particles[0].r0_(2);

    t.vx(0, 0) = t.particles[0].v0_(0);
    t.vy(0, 0) = t.particles[0].v0_(1);
    t.vz(0, 0) = t.particles[0].v0_(2);

    t.x(0, 1) = t.particles[1].r0_(0);
    t.y(0, 1) = t.particles[1].r0_(1);
    t.z(0, 1) = t.particles[1].r0_(2);

    t.vx(0, 1) = t.particles[1].v0_(0);
    t.vy(0, 1) = t.particles[1].v0_(1);
    t.vz(0, 1) = t.particles[1].v0_(2);

    t.time(0) = 0;

    t.r(0) = t.x(0, 0);
    t.r(1) = t.y(0, 0);
    t.r(2) = t.z(0, 0);

    t.v(0) = t.vx(0, 0);
    t.v(1) = t.vy(0, 0);
    t.v(2) = t.vz(0, 0);

    t.Forward_Euled(t.dt);

    std::cout << t.z << std::endl;

    std::string filename = "FE_table_2.csv";
    std::ofstream ofile;
    ofile.open("FE_table_2.csv"); 

    ofile <<"x[μm], y[μm], z[μm], v_x[μm/μs], v_y[μm/μs], v_y[μm/μs], t[μm]"<<std::endl;

    int width = 15;
    int prec  = 6;

    for(int i=0; i<t.n+1;i++)
    {
        ofile << std::setw(width) << std::setprecision(prec) << std::scientific << t.x(i, 1) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << t.y(i, 1) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << t.z(i, 1) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << t.vx(i, 1) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << t.vy(i, 1) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << t.vz(i, 1) << "," 
        << std::setw(width) << std::setprecision(prec) << std::scientific << t.time(i) << std::endl; 
    }


    return 0;
}