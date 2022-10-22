#include <iostream>
#include <armadillo>
#include <vector>
#include "trap.hpp"
#include "trap.cpp"

int main()
{
    double q = 0.3;
    double m = 2;
    arma::vec r(3);
    r(0) = 1;
    r(1) = 2;
    r(2) = 3;
    arma::vec v(3);
    v(0) = 4;
    v(1) = 5;
    v(2) = 6;

    double B = 1;
    double V = 6;
    double d = 9;

    particle p = particle(q, m, r, v);

    trap t = trap(B, V, d);

    t.add_particle(p);
    
    t.external_B_field();
    t.external_E_field(r);
    t.total_force_external();


    std::cout << t.F_ext << std::endl;

    return 0;
}