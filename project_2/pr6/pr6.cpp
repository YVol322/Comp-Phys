#include <iostream>
#include <armadillo>

double maxim(arma::mat& A, int& k, int& l, int N);

void JacS(arma::mat& A, arma::mat& R, int k, int l, int N);

void JacF(arma::mat& A, arma::mat& R, int k, int l, int N, double e);

int main()
{
    int N = 9; //number of cols and rows of A matrix
    int n = N + 1;
    double h = 1./n;

    double e = pow(10, -6);

    //creating .csv file to wtrite data into it
    std::string filename = "pr6table.csv";
    std::ofstream ofile;
    ofile.open("pr6table.csv"); 
        
    //addind header
    ofile <<"beam coordinate x_hat, 1st J eigvector, 2nd Jeidvector, 3rd Jeigvector, "
    << "1st J eigvector, 2nd Jeidvector, 3rd Jeigvector" << std::endl
    << "0, 0, 0, 0, 0, 0, 0" << std::endl; //adding boundary point at x_hat = 0

    int k;
    int l;

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

    JacF(A, R, k, l, N, e);

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

    arma::vec x(N);


    //on pr2.cpp we proved that solution of arma::eig_sym is literally the same as analytical.
    //So I outputed eig_sym solution.

    //outputing data
    for(int i = 0; i<N; i++)
    {
        x(i) = 1./n * (i + 1);
        ofile << x(i) << "," << Jeigvec(i, 0) << "," << Jeigvec(i, 1) 
        << "," << Jeigvec(i, 2) << "," << eigvec(i, 0) << "," << eigvec(i, 1) 
        << "," << eigvec(i, 2) <<std::endl;
    }

    //outputing boundary point at x_hat = 1
    ofile << "1, 0, 0, 0, 0, 0, 0";

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

void JacF(arma::mat& A, arma::mat& R, int k, int l, int N, double e)
{
    while(abs(maxim(A, k, l, N)) > e)
    {
        JacS(A, R, k, l, N);
    }
}