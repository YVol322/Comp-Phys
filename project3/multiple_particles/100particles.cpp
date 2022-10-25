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
    int N = 5;

    double B = 96.5;
    double V = 2.41 * pow(10, 6);
    double d = 500;

    arma::mat r_init = arma::mat(3, N).randn() * 0.1 * d;
    arma::mat v_init = arma::mat(3, N).randn() * 0.1 * d;

    trap t = trap(B, V, d);

    t.add_N_particles(N, r_init, v_init, q, m);

    t.N = N;
    t.r = r_init;
    t.v = v_init;
    t.t0 = 0.;

    t.n = 400000.;
    t.total_time = 500;
    t.dt = t.total_time/t.n;

    t.setsize();

    t.f = 0.1;
    t.Wv = 0.2;

    for(int i = 0; i<N; i++)
    {
    t.x(0, i) = r_init(0, i);
    t.y(0, i) = r_init(1, i);
    t.z(0, i) = r_init(2, i);


    t.vx(0, i) = v_init(0, i);
    t.vy(0, i) = v_init(1, i);
    t.vz(0, i) = v_init(2, i);
    }

    t.r = r_init;
    t.v = v_init;

    t.RK4(t.dt);

    std::cout << t.number_of_particles(t.r) << std::endl;
    std::cout << t.number_of_particles(r_init) << std::endl;

    //std::string filename = "FE4_table_100ms.csv";
    //std::ofstream ofile;
    //ofile.open("FE4_table_100ms.csv"); 
//
    //ofile <<"x1[μm], y1[μm], z1[μm], v_x1[μm/μs], v_y1[μm/μs], t[μs]" << std::endl;
//
    //int width = 15;
    //int prec  = 6;
//
    //for(int i=0; i<t.n+1;i++)
    //{
    //    ofile << std::setw(width) << std::setprecision(prec) << std::scientific << t.x(i, 0) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.y(i, 0) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.z(i, 0) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.vx(i, 0) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.vy(i, 0) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.vz(i, 0) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.time(i) << std::endl; 
    //}


    return 0;
}