#include <iostream>
#include <armadillo>


// maxim - function that finds larges off-diag. element, returns it's value and saves it's indexes to ints (k,l).

// input: A - A matrix, k & l - future col and row indexes of the largest element
// N - number of cols/rows of A matrix.

// output: larges off-diag. element; updates (k,l) indexes.
double maxim(arma::mat& A, int& k, int& l, int N);

int main()
{
    int N = 4; //number of cols and rows of A matrix
    int k; //row index of the largest element in the uword type
    int l; //column index of the largest element in the uword type

    //creating A matrix
    arma::mat A(N, N, arma::fill::zeros);

    //filling A matrix
    arma::vec a(N, arma::fill::ones);
    A.diag() = a;
    A(3) = 0.5;
    A(6) = -0.7;
    A(9) = -0.7;
    A(12) = 0.5;

    //outputing A matrix, it's largest element, indexes of this element
    //and making sure A(k,l) and A(l,k) are the larges elements
    std::cout << "Matrix A" << std::endl << A << std::endl
    << "Largest non-diag element of A" << std::endl<< maxim(A, k, l, N) << std::endl
    << "row number of 1st largest element" << std::endl << k << std::endl
    << "column number of 2nd largest element" << std::endl << l << std::endl
    << "Making sure A(k,l) is the largest element" << std::endl << A(k,l) << std::endl
    << "Making sure A(l,k) is also the largest element"<< std::endl << A(l,k) << std::endl;

    return 0;
}

double maxim(arma::mat& A, int& k, int& l, int N)
{
    double Amax; //creating value that will contin largest off-diag. element
    Amax = 0; //stetting initial Amax to 0

    arma::mat Atemp(N,N); //creating matrix
    Atemp = A; // A is a pointer to original A matrix. So we are cloning A matrix to Atemp

    arma::vec temp(N); //creating vector

    //next 2 lines is done not to touch diagonal elements
    temp = Atemp.diag(); //saving diagonal elements of A to temp vector
    A.diag().fill(0); //replacing diagonal elements of A by zeros

    //finding the largest off-diagonal element and saving it's indexes to k,l ints
    for(int i =0; i<N;i++)
    {
        for(int j = 0; j< i;j++)
        {
            if( abs(A(i,j)) > abs(Amax))
            {
                Amax = A(i, j);
                k = i; //updating k index
                l = j; //updating l index
            }
        }
    }

    A.diag() = temp; //bringing back the original diagonal elements
    return Amax; //returning the lagest off-diag element
}