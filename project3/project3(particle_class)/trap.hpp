#ifndef __trap_hpp__   
#define __trap_hpp__

#include <armadillo>
#include <vector>
#include "particle.hpp"
#include "particle.cpp"

class trap
{
    public:
        double B0_in, V0_in, d_in;

        std::vector<particle> particles;

        trap(double B0, double V0, double d);

        void add_particle(particle particle_input);

        int size();
};


//double external_el_field(std::vector<particle> particle_parameters_, double V0, double d);

//double external_mag_field(std::vector<particle> particle_parameters_, double B0, double d);

//double particles_interaction_force(std::vector<particle> particle_parameters_, double B0, double V0, double d);


#endif