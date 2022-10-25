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
    int N = 100;

    double B = 96.5;
    double V = 2.41 * pow(10, 6);
    double d = 500;

    arma::mat r_init = arma::mat(3, N).randn() * 0.1 * d;
    arma::mat v_init = arma::mat(3, N).randn() * 0.1 * d;

    trap t = trap(B, V, d);
    t.setsize();

    t.add_N_particles(N, r_init, v_init, q, m);

    std::cout << v_init.col(99) << std::endl;
    std::cout << t.particles[99].v0_ << std::endl;
    std::cout << t.d_ << std::endl;

    

    //std::cout << t.r << std::endl;
    //std::cout << t.v << std::endl;

    //std::string filename = "RK4_table_2_int.csv";
    //std::ofstream ofile;
    //ofile.open("RK4_table_2_int.csv"); 
//
    //ofile <<"x1[μm], y1[μm], z1[μm], v_x1[μm/μs], v_y1[μm/μs], v_y1[μm/μs],"
    //<<"x2[μm], y2[μm], z2[μm], v_x2[μm/μs], v_y2[μm/μs], v_y2[μm/μs], t[μs]" << std::endl;
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
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.x(i, 1) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.y(i, 1) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.z(i, 1) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.vx(i, 1) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.vy(i, 1) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.vz(i, 1) << ","
    //    << std::setw(width) << std::setprecision(prec) << std::scientific << t.time(i) << std::endl; 
    //}


    return 0;
}