#ifndef __particle_hpp__   
#define __particle_hpp__
#include <armadillo>

class particle
{    
    public:
        double q_, m_;
        arma::vec r_, v_;
        
        particle(double q, double m, arma::vec r, arma::vec v);

        double charge();
        double mass();
        arma::vec coordinates();
        arma::vec velocity();
        
};

#endif