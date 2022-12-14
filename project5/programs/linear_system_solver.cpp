#include <iostream>
#include <armadillo>

//function that fills A matrix
arma::cx_mat fill_A_matrix(arma::cx_mat V, double dt, double h, int M);

//function that fills B matrix
arma::cx_mat fill_B_matrix(arma::cx_mat V, double dt, double h, int M);


//function that transforms indexes i,j into index k
int get_index(int i, int j, int M);

int main()
{
    int M = 3;   // (M-2) = 3
    double dt = 0.2; //time step
    double h = 0.2;  //discrete step
    arma::cx_mat A = arma::cx_mat(M*M,M*M); //A matrix
    arma::cx_mat B = arma::cx_mat(M*M,M*M); //B matrix

    arma::cx_vec u = arma::cx_vec(M*M, arma::fill::randu);  //column-vector of U matrix

    arma::cx_mat V = arma::cx_mat(M*M,M*M, arma::fill::randu);  //potential matrix

    A = fill_A_matrix(V,dt,h,M);    //using the function to fill A matrix
    B = fill_B_matrix(V,dt,h,M);    //using the function to fill B matrix

    arma::cx_vec b(M*M);    //vecor result of multiolying A*u

    b = A * u;

    arma::cx_vec x(M*M);    //solution of a linear system vector

    x = arma::solve(A, b);  //using built-in arma solver

    std::string filename = "linear_system_solution.txt";    //expoting reuslt to the .txt file
    std::ofstream ofile;
    ofile.open("linear_system_solution.txt");

    ofile << "u vector" << std::endl;
    ofile << u << std::endl;
    ofile << std::endl;

    ofile << "V matrix" << std::endl;
    ofile << V << std::endl;
    ofile << std::endl;

    ofile << "A matrix" << std::endl;
    ofile << A << std::endl;
    ofile << std::endl;

    ofile << "b = A*u vector" << std::endl;
    ofile << b << std::endl;
    ofile << std::endl;

    ofile << "solution of a linear system x" << std::endl;
    ofile << x << std::endl;

    return 0;
}

arma::cx_mat fill_A_matrix(arma::cx_mat V, double dt, double h, int M)
{
    arma::cx_mat A(M*M,M*M);
    arma::cx_vec a(M*M*M*M);

    arma::cx_double r = arma::cx_double(0, dt/(2*h*h));

    for(int i=0; i<M*M;i++)
    {
        for(int j=0;j<M*M;j++)
        {
            int k = get_index(j,i, M);
            
            a(k) = arma::cx_double(1,0) + arma::cx_double(4,0) * r + arma::cx_double(0,dt/2) * V(j,i);
        }
    }

    arma::cx_vec a_9(M*M);

    for(int i=0;i<M*M;i++)
    {
        a_9(i) = a(i*M*M + i);
    }

    A.fill(arma::cx_double(0,0));  //filling matrix with 0
    A.diag() = a_9;   //setting diagonal elements to vector a
    A.diag(-3).fill(-r);    //filling -1,1,-3,3 diagonals with -r
    A.diag(3).fill(-r);
    A.diag(-1).fill(-r);
    A.diag(1).fill(-r);


    //setting every third element on 3 and -3 diagonals to zeros
    for(int i=0;i<M-1;i++)
    {
        A(M*i+M,M*i+M-1)=arma::cx_double(0,0);
        A(M*i+M-1,M*i+M)=arma::cx_double(0,0);
    }

    return A;
}

arma::cx_mat fill_B_matrix(arma::cx_mat V, double dt, double h, int M)
{
    arma::cx_mat B = arma::cx_mat(M*M,M*M);
    arma::cx_vec b = arma::cx_vec(M*M*M*M);

    arma::cx_double r = arma::cx_double(0, dt/(2*h*h));

    for(int i=0; i<M*M;i++)
    {
        for(int j=0;j<M*M;j++)
        {
            int k = get_index(j,i, M);

            b(k) = arma::cx_double(1,0) - arma::cx_double(4,0) - r + arma::cx_double(0,dt/2) * V(j,i);
        }
    }

    arma::cx_vec b_9(M*M);

    for(int i=0;i<M*M;i++)
    {
        b_9(i) = b(i*M*M + i);
    }


    B.fill(arma::cx_double(0,0));  //filling matrix with 0
    B.diag() = b_9;   //setting diagonal elements to vector a
    B.diag(-3).fill(r);    //filling -1,1,-3,3 diagonals with -r
    B.diag(3).fill(r);
    B.diag(-1).fill(r);
    B.diag(1).fill(r);

    //setting every third element on 3 and -3 diagonals to zeros
    for(int i=0;i<M-1;i++)
    {
        B(M*i+M,M*i+M-1)=arma::cx_double(0,0);
        B(M*i+M-1,M*i+M)=arma::cx_double(0,0);
    }

    return B;
}

// i stands for col number, j stands for row number
int get_index(int i, int j, int M)
{
    int k = j*M*M + i;
    return k;
}