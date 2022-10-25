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

    t.add_N_particles(N, r_init, v_init, q, m);

    t.N = N;
    t.r = r_init;
    t.v = v_init;
    t.t0 = 0.;

    t.n = 4000.;
    t.total_time = 500;
    t.dt = t.total_time/t.n;

    t.setsize();


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

    arma::mat W(48, 3);
    arma::mat number(48, 3);

    for(int i = 0; i<3; i++)
    {
        t.f = 0.1 + i * 0.3;
        for(int j = 0; j<48;j++)
        {  
            t.Wv = 0.2 + 0.05 *j;
            W(j,i) = t.Wv;
            t.RK4(t.dt);
            number(j,i) = t.number_of_particles(t.r);

            std::cout << t.number_of_particles(t.r) << std::endl;
            std::cout << t.number_of_particles(r_init) << std::endl;
            std::cout << "i " << i << "j " << j << std::endl;

            for(int k = 0; k<N; k++)
                {
                t.x(0, k) = r_init(0, k);
                t.y(0, k) = r_init(1, k);
                t.z(0, k) = r_init(2, k);


                t.vx(0, k) = v_init(0, k);
                t.vy(0, k) = v_init(1, k);
                t.vz(0, k) = v_init(2, k);

                t.r = r_init;
                t.v = v_init;
                }
        }
    }

    std::string filename = "RK4_table_500m_50p.csv";
    std::ofstream ofile;
    ofile.open("RK4_table_500m_50p.csv"); 

    ofile <<"n1, n2, n3, W" << std::endl;

    int width = 7;
    int prec  = 3;

    for(int i=0; i<48;i++)
    {
        ofile << std::setw(width) << std::setprecision(prec) << std::scientific << number(i,0) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << number(i,1) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << number(i,2) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << W(i, 0) << std::endl; 
    }


    return 0;
}