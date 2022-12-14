#include <iostream>
#include <armadillo>

//function that fills A matrix
arma::cx_mat fill_A_matrix(arma::cx_mat A, arma::cx_double r, arma::cx_vec a, int M);

//function that fills B matrix
arma::cx_mat fill_B_matrix(arma::cx_mat B, arma::cx_double r, arma::cx_vec b, int M);

int main()
{
    int M = 3;   // (M-2) = 3
    arma::cx_mat A(M*M, M*M);   //empty complex matrix A
    arma::cx_mat B(M*M, M*M);   //empty complex matrix B

    arma::cx_vec a(M*M, arma::fill::randu);     //random complex vector a
    arma::cx_vec b(M*M, arma::fill::randu);     //random complex vector b

    arma::cx_double r = arma::cx_double(2.0,3.0);   //random complex double r


    arma::cx_mat A_new = fill_A_matrix(A,r,a,M);    //assigning A_new to the filled A matrix

    arma::cx_mat B_new = fill_B_matrix(B,r,b,M);    //assigning B_new to the filled B matrix

    std::string filename = "9x9_matrices.txt";    //expoting reuslt to the .txt file
    std::ofstream ofile;
    ofile.open("9x9_matrices.txt"); 

    ofile << "A matrix" <<std::endl;
    ofile << A_new <<std::endl;
    ofile << "B matrix" <<std::endl;
    ofile << B_new <<std::endl;



    return 0;
}

arma::cx_mat fill_A_matrix(arma::cx_mat A, arma::cx_double r, arma::cx_vec a, int M)
{
    A.fill(0);  //filling matrix with 0
    A.diag() = a;   //setting diagonal elements to vector a
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

arma::cx_mat fill_B_matrix(arma::cx_mat B, arma::cx_double r, arma::cx_vec b, int M)
{
    B.fill(0);      //filling matrix with 0
    B.diag() = b;       //setting diagonal elements to vector b
    B.diag(-3).fill(r);     //filling -1,1,-3,3 diagonals with r
    B.diag(3).fill(r);
    B.diag(-1).fill(r);
    B.diag(1).fill(r);
    
    //setting every third element on 3 and -3 diagonals to zeros
    for(int i=0;i<int((M*M-1)/M);i++)
    {
        B(3*i+3,3*i+2)=arma::cx_double(0,0);
        B(3*i+2,3*i+3)=arma::cx_double(0,0);
    }

    return B;
}