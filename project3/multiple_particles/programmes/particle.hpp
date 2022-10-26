#ifndef __particle_hpp__   
#define __particle_hpp__
#include <armadillo>

class particle
{    
    public:
        double q_, m_;
        arma::vec r0_, v0_;
        
        particle(double q, double m, arma::vec r, arma::vec v);
        
};

#endif