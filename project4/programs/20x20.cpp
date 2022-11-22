#include <iostream>
#include <armadillo>
#include <fstream>

//function that computes current energy
double energy(arma::mat spin, int legth, int N);

//function that computes current magnetisation
double magnetisation(arma::mat spin, int length, int N);

//function that flips 1 spin in the spin matrix
arma::mat flip_1_spin(arma::mat spin, int length);

//function that computes mean energy
double mean_energy(arma::vec ens, int number_of_states);

//function that computes mean magnetization
double mean_magnetization(arma::vec magns, int number_of_states);

//function that computes <E^2>
double mean_energy_square(arma::vec ens, int number_of_states);

//function that computes <M^2>
double mean_magnetization_square(arma::vec magns, int number_of_states);

//function that compures heat capacity
double heat_cap(double mean_en, double mean_en_sq, double temp, int num_spins);

//function that compures susceptibility
double susp(double mean_magn, double mean_magn_sq, double inv_temp, int num_spins);



int main()
{
    arma::arma_rng::set_seed(4);
    
    arma::vec Temps(2);
    Temps(0) = 1;
    Temps(1) = 2;

    int L = 20; //length of lattice
    int N = L*L; // numer of spins in lattice

    int J = 1; //coupling constant

    double E=0; //energy per spin
    double M=0; //magnetization per spin
    double E_new=0; //new energy per spin

    int n = 200 * N; //number of MCMC cyclce

    int delta_E; //difference between current energy and new energy

    arma::mat s(L,L); //matrix that contains all spins 
    arma::mat s_candidate(L,L); //candidate for new state spin matrix

    arma::vec energies(n+1); //vector that contains all energies
    arma::vec magnetisations(n+1); //vector that contains all magnetizations

    double w=0;
    double r=0;

    std::string filename = "20x20_table_+1.csv";
    std::ofstream ofile;
    ofile.open("20x20_table_+1.csv"); 
    //std::string filename = "20x20_T=2.4_table.csv";
    //std::ofstream ofile;
    //ofile.open("20x20_T=2.4_table.csv"); 

    ofile <<"n, <eps> [J], <|m|>" << std::endl;

    int width = 15;
    int prec  = 6;

    for(int l =0; l<2; l++)
    {
        double T = Temps(l);
        double beta = 1./T;

        s = arma::ones(L,L);
    
        ////initilising random state of the system
        //for(int i=0; i<L; i++)
        //{
        //    for(int j=0; j<L; j++)
        //    {
        //        int k = arma::randi();
//
        //        if(k%2 ==0)
        //        {
        //            s(i,j) = 1;
        //        }
        //        else
        //        {
        //            s(i,j) = -1;
        //        }
        //    }
        //}

        E = energy(s,L,N); //energy of 1st state
        energies(0) = E; //adding it to the list

        M = magnetisation(s,L,N); //magnetization of 1st state
        magnetisations(0)= M; //adding it to the list

        //initial state s, E, M
        //std::cout << "s " << std::endl << s << std::endl;
        //std::cout << "E " << E << std::endl;
        //std::cout << "M " << M << std::endl;

        //MCMC algo
        for(int k = 1; k<=n;k++)
        {
            std::cout << k << std::endl;
            s_candidate = flip_1_spin(s,L);

            E_new = energy(s_candidate,L,N);
            delta_E = E_new - E;

            if(delta_E<=0)
            {
                s = s_candidate;

                E = E_new;
                energies(k) = E;

                M = magnetisation(s,L,N);
                magnetisations(k)= M;
            }
            else
            {
                w = exp(-beta * delta_E);
                r = arma::randn();
                if (r<=w)
                {
                    s = s_candidate;

                    E = E_new;
                    energies(k) = E;

                    M = magnetisation(s,L,N);
                    magnetisations(k)= M;
                }
                else
                {
                    s = s;

                    energies(k) = E;
                    magnetisations(k)= M;
                }
            }

            ofile << std::setw(width) << std::setprecision(prec) << std::scientific << double(k)/N << ","
            << std::setw(width) << std::setprecision(prec) << std::scientific << mean_energy(energies, k+1) << ","
            << std::setw(width) << std::setprecision(prec) << std::scientific << mean_magnetization(energies, k+1) << std::endl; 
        }
    }

    return 0;
}

double energy(arma::mat spin, int length, int N)
{
    double E_temp=0;
    for(int i=0; i<length; i++)
    {
        for(int j=0; j<length; j++)
        {
            E_temp+= -1./N * spin(i,j) * (int(spin(-i+length-1,j)) + int(spin(i,-j+length-1)));
        }
    }
    return E_temp;
}

double magnetisation(arma::mat spin, int length, int N)
{
    double M_temp=0;
    for(int i=0; i<length; i++)
    {
        for(int j=0; j<length; j++)
        {
            M_temp+= 1./N* spin(i,j);
        }
    }
    return M_temp;
}

arma::mat flip_1_spin(arma::mat spin, int length)
{
    int change_index_1, change_index_2;
    change_index_1 = arma::randi(arma::distr_param(0, length-1));
    change_index_2 = arma::randi(arma::distr_param(0, length-1));

    spin(change_index_1, change_index_2) = spin(change_index_1, change_index_2) * (-1);
    return spin;
}

double mean_energy(arma::vec ens, int number_of_states)
{
    double en_sum=0.;
    double en_avg;
    for(int j=0;j<number_of_states;j++)
    {
        en_sum = en_sum + ens(j);
    }
    en_avg = en_sum/double(number_of_states);
    return en_avg;
}

double mean_magnetization(arma::vec magns, int number_of_states)
{
    double mag_sum=0.;
    double mag_avg;
    for(int j=0;j<number_of_states;j++)
    {
        mag_sum = mag_sum + abs(magns(j));
    }
    mag_avg = mag_sum/double(number_of_states);
    return mag_avg;
}


double mean_energy_square(arma::vec ens, int number_of_states)
{
    double en_sum_squares=0.;
    double en_avg_squares;
    for(int j=0;j<number_of_states;j++)
    {
        en_sum_squares = en_sum_squares + ens(j)*ens(j);
    }
    en_avg_squares = en_sum_squares/double(number_of_states);
    return en_avg_squares;
}

double mean_magnetization_square(arma::vec magns, int number_of_states)
{
    double mag_sum_squares=0.;
    double mag_avg_squares;
    for(int j=0;j<number_of_states;j++)
    {
        mag_sum_squares = mag_sum_squares + magns(j)*magns(j);
    }
    mag_avg_squares = mag_sum_squares/double(number_of_states);
    return mag_avg_squares;
}


double heat_cap(double mean_en, double mean_en_sq, double temp, int num_spins)
{
    double C=0;
    C = 1/(num_spins*temp*temp) * (mean_en_sq - mean_en * mean_en);
    return C;

}


double susp(double mean_magn, double mean_magn_sq, double inv_temp, int num_spins)
{
    double X=0;
    X = inv_temp/num_spins * (mean_magn_sq - mean_magn * mean_magn);
    return X;
}