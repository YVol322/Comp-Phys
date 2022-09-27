#include <iostream>
#include <armadillo>
#include <fstream>


double maxim(arma::mat& A, int& k, int& l, int N);

void JacS(arma::mat& A, arma::mat& R, int k, int l, int N);

void JacF(arma::mat& A, arma::mat& R, int k, int l, int N, double e, int& j); //aded int j - number of iterations as input

int main()
{
    int N;

    //creating .csv file to wtrite data into it
    std::string filename = "pr5table.csv";
    std::ofstream ofile;
    ofile.open("pr5table.csv"); 

    //addind header
    ofile <<"Number of cols/rows of A/R matrix, Number of iterations j"<<std::endl;

    //performing full Jacobi's algo for different N
    for(N=4; N<41; N++)
    {
        int n = N + 1;
        double h = 1./n;

        double e = pow(10, -6);

        int k;
        int l;

        int j; // number of iterations

        arma::mat A(N, N, arma::fill::zeros);

        arma::vec a(N-1);
        arma::vec d(N);
        a.fill(-1/(h*h));
        d.fill(2/(h*h));
        A.diag() = d;
        A.diag(-1) = a;
        A.diag(1) = a;

        arma::vec eigval(N);
        arma::mat eigvec(N, N);

        arma::eig_sym(eigval, eigvec, A);

        eigval = arma::normalise(eigval);
        eigvec = arma::normalise(eigvec);

        arma::mat R(N, N, arma::fill::zeros);

        arma::vec z(N, arma::fill::ones);
        R.diag() = z;

        JacF(A, R, k, l, N, e, j);

        arma::vec Jeigval_not_sorted(N);
        arma::vec Jeigval(N);

        arma::vec sindexes(N);
        arma::vec nindexes(N);
        arma::mat Jeigvec(N,N);

        Jeigvec = R;
        Jeigval_not_sorted = arma::normalise(A.diag());

        Jeigval = arma::sort(Jeigval_not_sorted);

        for(int i = 0; i<N; i++)
        {
            for(int j =0; j<N;j++)
            {
                if(Jeigval(i) == Jeigval_not_sorted(j))
                {
                    sindexes(i) = i;
                    nindexes(i) = j;
                }
            }
            Jeigvec.col(sindexes(i)) = R.col(nindexes(i));
        }

        //outputing Jacobi's algo eigvals and eigvecs & arma::eig_sym eigvals and eigvecs

        //if you want to make sure algo is working well for N != 6 uncomment next lines 91-92.

        std::cout //<< "arma::eig_sym eigvalues" << std::endl << eigval << std::endl 
        //<< "Jacobi's algo eigvalues" << std::endl << Jeigval << std::endl
        << "Number of cols/rows of A/R matrix" << std::endl << N << std::endl
        << "Number of iterations" << std::endl << j << std::endl;

        //outputing N & j to file
        ofile << N << "," << j <<std::endl;

        j = 0;//setting j to 0
    }

    return 0;
}

double maxim(arma::mat& A, int& k, int& l, int N)
{
    double Amax;
    Amax = 0;

    arma::mat Atemp(N,N);
    Atemp = A;

    arma::vec temp(N);
    temp = Atemp.diag();
    A.diag().fill(0);
    
    for(int i =0; i<N;i++)
    {
        for(int j = 0; j< i;j++)
        {
            if( abs(A(i,j)) > abs(Amax))
            {
                Amax = A(i, j);
                k = i;
                l = j;
            }
        }
    }
    A.diag() = temp;
    return Amax;
}

void JacS(arma::mat& A, arma::mat& R, int k, int l, int N)
{
    double q;
    q = maxim(A, k, l, N);

    double tau;

    if(k>l)
    {
        tau = (A(l, l) - A(k, k))/(2 * q);
    }
    else
    {
        tau = (A(k, k) - A(l, l))/(2 * q);
    }

    double t1;
    double t2;
    double t;
    double s;
    double c;

    t1 = -tau + sqrt(1 + pow(tau, 2));
    t2 = -tau - sqrt(1 + pow(tau, 2));

    if(t1>t2)
    {
        t = t2;
    }
    else
    {
        t = t1;
    }

    c = 1/sqrt(1 + pow(t, 2));
    s = c * t;

    double g;
    g = A(k,k);
    A(k, k) = A(k, k) * pow(c, 2) - 2 * A(k, l) * s * c + A(l, l) * pow(s, 2);
    A(l, l) = A(l, l) * pow(c, 2) + 2 * A(k, l) * s * c + g * pow(s, 2);
    A(k, l) = 0;
    A(l, k) = 0;

    for(int i = 0; i < N; i++)
    {
    
        while(i == k || i ==l)
            {
                i++;
            }

        if (i>N-1)
        {
            break;
        }
    
        double x;
        x = A(i,k);

        A(i,k) = A(i, k) * c - A(i, l) * s;
        A(k, i) = A(i, k);
        A(i,l) = A(i, l) * c + x * s;
        A(l, i) = A(i, l);
    }

    for (int i = 0; i<N; i++)
    {
        double b;
        b = R(i, k);
        R(i, k) = R(i, k) * c - R(i, l) * s;
        R(i, l) = R(i, l) * c + b * s;
    }

}

void JacF(arma::mat& A, arma::mat& R, int k, int l, int N, double e, int& j)
{

    //performing JacS() while largest off-diag. element is bigger then
    while(abs(maxim(A, k, l, N)) > e)
    {
        JacS(A, R, k, l, N);

        //saving the iterations number
        j++;
    }
}