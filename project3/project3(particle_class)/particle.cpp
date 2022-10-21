#include "particle.hpp"

particle::particle(double q, double m, arma::vec r, arma::vec v)
{
    q_ = q;
    m_ = m;
    r_ = r;
    v_ = v;
}

double particle::charge()
{
    return q_;
}

double particle::mass()
{
    return m_;
}

arma::vec particle::coordinates()
{
    return r_;
}

arma::vec particle::velocity()
{
    return v_;
}