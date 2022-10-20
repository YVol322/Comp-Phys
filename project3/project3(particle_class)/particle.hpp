#ifndef __particle_hpp__   
#define __particle_hpp__
#include <armadillo>

class particle
{
    protected:
        double q_, m_;
        arma::vec r_, v_;
    
    public:
        particle(double q, double m, arma::vec r, arma::vec v);
};

#endif