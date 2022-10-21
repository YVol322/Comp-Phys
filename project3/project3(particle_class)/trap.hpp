#ifndef __trap_hpp__   
#define __trap_hpp__
#include <armadillo>
#include <vector>
#include "particle.hpp"

class trap
{   
    public:
        double B0_, V0_, d_;
        std::vector<particle> particle_parameters_;
        
        trap(double B0, double V0, double d, std::vector<particle> particle_parameters);
};


//double external_el_field(std::vector<particle> particle_parameters_, double V0, double d);

//double external_mag_field(std::vector<particle> particle_parameters_, double B0, double d);

//double particles_interaction_force(std::vector<particle> particle_parameters_, double B0, double V0, double d);


#endif