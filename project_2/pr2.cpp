#include <iostream>
#include <armadillo>
#include <math.h>

int main()
{
    int N = 6; // size of A matrix
    int n = N + 1;
    double h = 1./n; //discrete step

    //approimate solution

    arma::mat A(N, N, arma::fill::zeros); //matrix A

    //filling matrix A
    arma::vec a(N-1);
    arma::vec d(N);
    a.fill(-1/(h*h));
    d.fill(2/(h*h));
    A.diag() = d;
    A.diag(-1) = a;
    A.diag(1) = a;

    //outputing A matrix
    std::cout << "A matrix" << std::endl << A << std::endl;

    //creating vector of approximate eigvalues and matrix of approximate eigvectors (eigvetors are columns of matrix)
    arma::vec eigval(N);
    arma::mat eigvec(N, N);

    //arma decompoition (approximate solution for eigvalues/eigvectors problem)
    arma::eig_sym(eigval, eigvec, A);

    //normalisig appproximate eigvectors and eigvalues
    eigval = arma::normalise(eigval);
    eigvec = arma::normalise(eigvec);

    //analytical solution

    //creating vector of analytical eigvalues and matrix of analytical eigvectors (eigvetors are columns of matrix)
    arma::vec anval(N);
    arma::mat anvec(N, N);

    //filing the analytical eigvalues and eigvectors
    for(int i = 1; i < N+1; i++)
    {
        anval(i-1) = d(0) + 2 * a(0) * cos((i * M_PI)/(N+1));
        for(int j = 1; j < N + 1; j++)
        {
            anvec(j-1,i-1) = sin((i * j * M_PI)/(N+1));
        }
    }

    //normalisig analytical eigvectors and eigvalues
    anval = arma::normalise(anval);
    anvec = arma::normalise(anvec);

    //since v and const * v are the same eigenvectors, multiplying 2nd and 6th eigvector by (-1)
    anvec.col(1) = anvec.col(1) * (-1);
    anvec.col(5) = anvec.col(5) * (-1);

    //outputing approximate and analytical eigvectors and eigvalues
    std::cout << "analytical eigvalues" << std::endl << anval << std::endl 
    << "appproximate eigvalues" << std::endl << eigval << std::endl;

    std::cout << "analytical eigvectors (i column is an eigenvecor of i eigenvalue)" << std::endl << anvec << std::endl 
    << "appproximate eigvectors (i column is an eigenvecor of i eigenvalue)" << std::endl << eigvec << std::endl;

    return 0;
}