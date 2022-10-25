#ifndef __trap_hpp__   
#define __trap_hpp__

#include <armadillo>
#include <vector>
#include "particle.hpp"
#include "particle.cpp"

class trap
{
    public:
        double B0_, V0_, d_, k_e;

        std::vector<particle> particles;

        arma::vec E, B, F_ext, F_int, F_tot;

        arma::mat x, y, z, vx, vy, vz, time;

        arma::mat r, v, rtemp, vtemp;

        double dt, n, total_time, t0, current_time, N;

        arma::mat k1r, k2r, k3r, k4r;

        arma::mat k1v, k2v, k3v, k4v;

        arma::mat kravg, kvavg;

        double num;

        double Wv, f;

        double tt;

        trap(double B0, double V0, double d);

        void add_particle(particle particle_input);
        
        void add_N_particles(int Nu, arma::mat r, arma::mat v, double q, double m);

        void setsize();

        double V_dt(double current_time);

        double number_of_particles(arma::mat r);

        arma::vec external_E_field(arma::vec r, double current_time);

        arma::vec external_B_field(arma::vec r);

        arma::vec force_particle(int i, int j);///////////////////// didn't check

        arma::vec total_force_external(int i, double current_time);

        arma::vec total_force(int i, bool s, double current_time);

        void Forward_Euled(double dt);

        void RK4(double dt);



};


//double external_el_field(std::vector<particle> particle_parameters_, double V0, double d);

//double external_mag_field(std::vector<particle> particle_parameters_, double B0, double d);

//double particles_interaction_force(std::vector<particle> particle_parameters_, double B0, double V0, double d);


#endif