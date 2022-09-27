#include <iostream>
#include <armadillo>


double maxim(arma::mat& A, int& k, int& l, int N);


//JacS - function that performs singe iteration Jackobi's algo.

// input: A - A matrix, , R - R matrix, k & l - col and row indexes of the largest element
// N - number of cols/rows of A matrix.

// output: nothing, but changes A matrix, R matrix & (k,l) indexes
void JacS(arma::mat& A, arma::mat& R, int k, int l, int N);


//JacF - function that performs full Jacobi's algo.

// input: A - A matrix, , R - R matrix, k & l - col and row indexes of the largest element
// N - number of cols/rows of A matrix, e - tolerance.

// output: nothing, but changes A matrix & R matrix, so that A.diag() contains eigenvalues, R.col() cotains eigenvectors
void JacF(arma::mat& A, arma::mat& R, int k, int l, int N, double e);

int main()
{
    int N = 6; //number of cols and rows of A matrix
    int n = N + 1;
    double h = 1./n; //discrete step

    double e = pow(10, -6); //tolerance


    int k; //row index of the largest element in the uword type. Updated by using maxim()/JacS()/JacF()
    int l; //column index of the largest element in the uword type. Updated by using maxim()/JacS()/JacF()

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

    arma::mat R(N, N, arma::fill::zeros); //creating R matrix

    //filling the R matrix
    arma::vec z(N, arma::fill::ones);
    R.diag() = z;

    //performing full Jacobi's algo to the A & R matrixes
    JacF(A, R, k, l, N, e);

    arma::vec Jeigval_not_sorted(N); //not sorted eigenvalues recieved performing Jacobi's algo.
    arma::vec Jeigval(N); //sorted eigenvalues recieved by performing Jacobi's algo.


    //this vectors is needed to sort R matrix according to sort of Jeigval
    arma::vec sindexes(N); //sorted indexes
    arma::vec nindexes(N); //not sorted indexes
    arma::mat Jeigvec(N,N); //sorted matrix of eigvectors

    //sorting everything that needs to be sorted
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

    //outputing Jacoi's algo eigvals and eigvecs & arma::eig_sym eigvals and eigvecs
    std::cout << "arma::eig_sym eigvalues" << std::endl << eigval << std::endl 
    << "Jacobi's algo eigvalues" << std::endl << Jeigval << std::endl
    << "arma::eig_sym eigvectors (i column is an eigenvecor of i eigenvalue)" << std::endl << eigvec << std::endl 
    << "Jacobi's algo eigvectors (i column is an eigenvecor of i eigenvalue)" << std::endl << Jeigvec << std::endl;

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
    double q; //temporary variable for the largest matrix element for updating (k, l) indexes
    q = maxim(A, k, l, N);

    double tau; //variable that makes A(k,l) = 0 on this iterate stage

    //filling tau
    if(k>l)
    {
        tau = (A(l, l) - A(k, k))/(2 * q);
    }
    else
    {
        tau = (A(k, k) - A(l, l))/(2 * q);
    }

    double t1; // 1st root tan(theta)
    double t2; // 2nd root tan(theta)
    double t; // smallest value tan(thaeta)
    double s; // sin(theta)
    double c; // cos(theta)

    //calculating t1 & t2
    t1 = -tau + sqrt(1 + pow(tau, 2));
    t2 = -tau - sqrt(1 + pow(tau, 2));

    //choosing lowest value tan(theta)
    if(t1>t2)
    {
        t = t2;
    }
    else
    {
        t = t1;
    }

    //filling sin(theta) and cos(theta)
    c = 1/sqrt(1 + pow(t, 2));
    s = c * t;

    //updating A matrix
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


    //updating R matrix
    for (int i = 0; i<N; i++)
    {
        double b;
        b = R(i, k);
        R(i, k) = R(i, k) * c - R(i, l) * s;
        R(i, l) = R(i, l) * c + b * s;
    }

}

void JacF(arma::mat& A, arma::mat& R, int k, int l, int N, double e)
{
    //performing JacS() while largest off-diag. element is bigger then
    while(abs(maxim(A, k, l, N)) > e)
    {
        JacS(A, R, k, l, N);
    }
}