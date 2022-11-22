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

    arma::vec Temps = arma::linspace(1,20, 20); //[T] = J/k_B

    int L = 2; //length of lattice
    int N = L*L; // numer of spins in lattice

    int J = 1; //coupling constant

    double E=0; //energy per spin
    double M=0; //magnetization per spin
    double E_new=0; //new energy per spin

    int n = 1000000 * N; //number of MCMC cyclce

    int delta_E; //difference between current energy and new energy

    arma::mat s(L,L); //matrix that contains all spins 
    arma::mat s_candidate(L,L); //candidate for new state spin matrix

    arma::vec energies(n+1); //vector that contains all energies
    arma::vec magnetisations(n+1); //vector that contains all magnetizations

    double w=0;
    double r=0;

    std::string filename = "2x2table.csv";
    std::ofstream ofile;
    ofile.open("2x2table.csv"); 
    
    ofile <<"T [J/k_B], <eps> an [j], <eps^2> an [j^2], <|m|> an, <m^2> an, C_V an [k_B], Chi an [1/J]" 
    << "<eps> pr [j], <eps^2> pr [j^2], <|m|> pr, <m^2> pr, C_V pr [k_B], Chi pr [1/J]" << std::endl;
    
    int width = 15;
    int prec  = 6;


   for(int l=0; l<20; l++)
    {   
   //initilising random state of the system
        for(int i=0; i<L; i++)
        {
            for(int j=0; j<L; j++)
            {
                int k = arma::randi();

                if(k%2 ==0)
                {
                    s(i,j) = 1;
                }
                else
                {
                    s(i,j) = -1;
                }
            }
        }

        E = energy(s,L,N); //energy of 1st state
        energies(0) = E; //adding it to the list

        M = magnetisation(s,L,N); //magnetization of 1st state
        magnetisations(0)= M; //adding it to the list

        //initial state s, E, M
        //std::cout << "s " << std::endl << s << std::endl;
        //std::cout << "E " << E << std::endl;
        //std::cout << "M " << M << std::endl;

        double T = Temps(l);
        double beta = 1./T;
        //MCMC algo
        for(int k = 1; k<=n;k++)
        {
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

        }

        double Z = 4*cosh(2*beta) +12; //partition function

        double analyt_mean_energy_ps = -8 * sinh(2*beta)/Z; //analyt <eps>
        double analyt_mean_energy_squared_ps = 16 * cosh(2*beta)/Z; //analyt <eps^2>
        double analyt_mean_magn_ps = 2 * (exp(2*beta)+2)/Z; //analyt <|m|>
        double analyt_mean_magn_squared_ps = 2 * (exp(2*beta)+1)/Z; //analyt <m^2>

        double m_en = mean_energy(energies, n+1); //progr <eps>
        double m_en_2 =  mean_energy_square(energies, n+1); //progr <eps^2>
        double m_mag = mean_magnetization(magnetisations, n+1); //progr <|m|>
        double m_mag_2 = mean_magnetization_square(magnetisations, n+1); //progr <m^2>

        std::cout <<  "l " << l << std::endl;
        std::cout <<  "<E> " << m_en << std::endl;
        std::cout <<  "<E> analyt " << analyt_mean_energy_ps << std::endl;
        //std::cout <<  "<E^2> " << m_en_2 << std::endl;
        //std::cout <<  "<E^2> analyt " << analyt_mean_energy_squared_ps << std::endl;
        //std::cout <<  "<M> " << m_mag << std::endl;
        //std::cout <<  "<M> analyt  " << analyt_mean_magn_ps << std::endl;
        //std::cout <<  "<M^2> " << m_mag_2 << std::endl;
        //std::cout <<  "<M^2 analyt > " << analyt_mean_magn_squared_ps << std::endl;
        //std::cout <<  "<C_V> " << heat_cap(m_en, m_en_2, T, N) << std::endl;
        //std::cout <<  "<C_V> analyt " << heat_cap(analyt_mean_energy_ps, analyt_mean_energy_squared_ps, T, N) << std::endl;
        //std::cout <<  "Chi " << susp(m_mag, m_mag_2, beta, N) << std::endl;
        //std::cout <<  "Chi analyt " << susp(analyt_mean_magn_ps, analyt_mean_magn_squared_ps, beta, N) << std::endl;


        ofile << std::setw(width) << std::setprecision(prec) << std::scientific << T << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << analyt_mean_energy_ps << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << analyt_mean_energy_squared_ps << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << analyt_mean_magn_ps << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << analyt_mean_magn_squared_ps << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << heat_cap(analyt_mean_energy_ps, analyt_mean_energy_squared_ps, T, N) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << susp(analyt_mean_magn_ps, analyt_mean_magn_squared_ps, beta, N) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << m_en << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << m_en_2 << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << m_mag << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << m_mag_2 << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << heat_cap(m_en, m_en_2, T, N) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << susp(m_mag, m_mag_2, beta, N) << std::endl; 
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