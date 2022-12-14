#include <iostream>
#include <armadillo>

//function that transforms indexes i,j into index k
int get_index(int i, int j, int M);

int main()
{
    int M = 5; // (M-2) = 3
    
    arma::cx_mat U = arma::cx_mat(M*M, M*M, arma::fill::randu); //random complex matrix U

    arma::cx_vec u = U.as_col();    //column vector u using as.col()

    std::string filename = "indexes_25x25.txt";    //expoting reuslt to the .txt file
    std::ofstream ofile;
    ofile.open("indexes_25x25.txt"); 

    ofile << "U matrix" << std::endl;
    ofile << U << std::endl;

    ofile << "U_(i,j) = U_(2,3)" << std::endl;
    ofile << U(20,21) << std::endl;
    ofile << "computed index k" << std::endl;
    ofile << get_index(20,21,M) << std::endl;
    ofile << "u_k" << std::endl;
    ofile << u(get_index(20,21,M)) << std::endl;
    ofile << std::endl;

    ofile << "U_(i,j) = U_(5,5)" << std::endl;
    ofile << U(13,15) << std::endl;
    ofile << "computed index k" << std::endl;
    ofile << get_index(13,15,M) << std::endl;
    ofile << "u_k" << std::endl;
    ofile << u(get_index(13,15,M)) << std::endl;
    ofile << std::endl;

    ofile << "U_(i,j) = U_(8,4)" << std::endl;
    ofile << U(2,20) << std::endl;
    ofile << "computed index k" << std::endl;
    ofile << get_index(2,20,M) << std::endl;
    ofile << "u_k" << std::endl;
    ofile << u(get_index(2,20,M)) << std::endl;
    ofile << std::endl;


    return 0;
}

// i stands for col number, j stands for row number
int get_index(int i, int j, int M)
{
    int k = j*M*M + i;
    return k;
}