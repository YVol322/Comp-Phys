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

    arma::vec r(3);
    r(0) = 20;
    r(1) = 0;
    r(2) = 20;

    arma::vec v(3);
    v(0) = 0;
    v(1) = 25;
    v(2) = 0;

    double B = 96.5;
    double V = 2.41 * pow(10, 6);
    double d = 500;

    particle p = particle(q, m, r, v);

    trap t = trap(B, V, d);

    t.n = 16000;
    t.t = 50;
    t.dt = t.t/t.n;

    t.add_particle(p);
    
    //t.Forward_Euled(t.dt);
//
    //t.r =r;
    //t.v = v;

    t.RK4(t.dt);

    std::cout << t.z << std::endl;
    std::cout << t.time << std::endl;

    std::string filename = "z_vs_t_16k.csv";
    std::ofstream ofile;
    ofile.open("z_vs_t_16k_table.csv"); 

    ofile <<"z[μm], t[μm]"<<std::endl;

    int width = 15;
    int prec  = 6;

    for(int i=0; i<t.n;i++)
    {
        ofile << std::setw(width) << std::setprecision(prec) << std::scientific << t.z(i) << "," 
        << std::setw(width) << std::setprecision(prec) << std::scientific << t.time(i) << std::endl; 
    }


    return 0;
}