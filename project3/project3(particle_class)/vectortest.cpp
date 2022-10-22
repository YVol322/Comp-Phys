#include <iostream>
#include <vector>
#include "particle.hpp"
#include "particle.cpp"


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

    particle p = particle(q, m, r, v);

    std::vector<particle> b;

    std::vector<int> q;

    b.push_back(p);


    q.push_back(int(3));
    std::cout << b.size();



    return 0;
}