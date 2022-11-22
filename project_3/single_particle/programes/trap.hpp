#ifndef __trap_hpp__   
#define __trap_hpp__

#include <armadillo>
#include <vector>
#include "particle.hpp"
#include "particle.cpp"

class trap
{
    public:
        double B0_, V0_, d_;

        std::vector<particle> particles;

        arma::vec E, B, F_ext;

        arma::vec x, y, z, vx, vy, vz, time;

        arma::vec r, v, rtemp, vtemp;

        double dt, n, t, t0;

        arma::vec k1r, k2r, k3r, k4r;

        arma::vec k1v, k2v, k3v, k4v;

        arma::vec kravg, kvavg;

        trap(double B0, double V0, double d);

        void add_particle(particle particle_input);

        arma::vec external_E_field(arma::vec r);

        arma::vec external_B_field();

        arma::vec total_force_external();

        void Forward_Euled(double dt);

        void RK4(double dt);



};


//double external_el_field(std::vector<particle> particle_parameters_, double V0, double d);

//double external_mag_field(std::vector<particle> particle_parameters_, double B0, double d);

//double particles_interaction_force(std::vector<particle> particle_parameters_, double B0, double V0, double d);


#endif