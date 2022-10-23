#include <iostream>
#include <armadillo>
#include <vector>
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

    t.n = 4000;
    t.t = 50;
    t.dt = t.t/t.n;

    t.add_particle(p);
    
    t.RK4(t.dt);


    std::cout << t.z << std::endl;
    std::cout << t.vz << std::endl;

    return 0;
}