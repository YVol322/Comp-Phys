#include <iostream>
#include <armadillo>


int main()
{
    int M = 200;
    double h = 1./M;

    arma::vec x(M); //vector with x points
    arma::vec y(M); //vector with y points


    //parameters of packet
    double x_c = 0.25;
    double y_c = 0;
    double s_x = 0.05;
    double s_y = 0.05;
    double p_x = 200;
    double p_y = 0;

    //x-x_c, y-y_c vectors
    arma::vec x_diff(M);
    arma::vec y_diff(M);

    std::string filename = "packet.txt";    //expoting reuslt to the .txt file
    std::ofstream ofile;
    ofile.open("packet.txt");

    //filling x-x_c, y-y_c vectors
    for(int i=0; i<M;i++)
    {
        x(i) = i*h;
        y(i) = i*h;

        x_diff(i) = x(i) - x_c;
        y_diff(i) = y(i) - y_c;
    }

    //computing U matrix
    arma::cx_mat U(M,M);

    for(int i=0;i<M;i++)
    {
        for(int j=0;j<M;j++)
        {
            double re = -x_diff(j)*x_diff(j)/(2*s_x*s_x) - y_diff(i)*y_diff(i)/(2*s_y*s_y);
            double im = p_x * x_diff(j) + p_y * y_diff(j);
            arma::cx_double p(re,im);

            U(j,i) = std::exp(p);
        }
    }

    //computing conj. matrix
    arma::cx_mat U_conj = arma::conj(U);

    //computing sum of U^*U
    arma::cx_double sum = arma::cx_double(0,0);

    for(int i=0;i<M;i++)
    {
        for(int j=0;j<M;j++)
        {
            sum += U(i,j) * U_conj(i,j);
        }
    }

    arma::cx_double sum_before = sum;
    

    //normalising U
    arma::cx_double norm = arma::cx_double(1./(sqrt(sum.real())),0);

    for(int i=0;i<M;i++)
    {
        for(int j=0;j<M;j++)
        {
            U(i,j) = U(i,j) * norm;
        }
    }

    U_conj = arma::conj(U);
    sum = arma::cx_double(0,0);

    for(int i=0;i<M;i++)
    {
        for(int j=0;j<M;j++)
        {
            sum += U(i,j) * U_conj(i,j);
        }
    }


    ofile << "x_c" << std::endl;
    ofile << x_c << std::endl;
    ofile << std::endl;

    ofile << "y_c" << std::endl;
    ofile << y_c << std::endl;
    ofile << std::endl;

    ofile << "sigma_x" << std::endl;
    ofile << s_x << std::endl;
    ofile << std::endl;

    ofile << "sigma_y" << std::endl;
    ofile << s_y << std::endl;
    ofile << std::endl;

    ofile << "p_x" << std::endl;
    ofile << p_x << std::endl;
    ofile << std::endl;

    ofile << "p_y" << std::endl;
    ofile << p_y << std::endl;
    ofile << std::endl;

    ofile << "h" << std::endl;
    ofile << h << std::endl;
    ofile << std::endl;

    ofile << "U matrix" << std::endl;
    ofile << U << std::endl;
    ofile << std::endl;

    ofile << "sum U^* U before normalization" << std::endl;
    ofile << sum_before << std::endl;
    ofile << std::endl;

    ofile << "sum U^* U after normalization" << std::endl;
    ofile << sum << std::endl;
    ofile << std::endl;







    return 0;
}