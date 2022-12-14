#include <iostream>
#include <armadillo>


int main()
{
    int M = 200;    //number of points in x and y direction (including boundary)
    double h = 1./M;  //discrete step

    double a = 0.02; //wall thickness
    double b = 0.05; // aperture & distanse between ends of the slits

    double a_points;
    double b_points;

    a_points = a/h; //wall thickness in terms of h
    b_points = b/h;  // aperture & distanse between ends of the slits in terms of h

    arma::mat V(M,M);   //potential matrix

    double v_0 = pow(10,6); //v_0

    for(int i=0;i<=a_points;i++)
    {
        V.col((0.49 + i*h)/h).fill(v_0);
    }

    for(int j=0;j<=b_points;j++)
    {
        V.row((0.425 + j * h)/h).fill(0);
        V.row((0.525 + j * h)/h).fill(0);
    }

    if(V(94,100)!=0)
    {
        V.row(94).fill(0);
    }

    std::string filename = "barrier.txt";    //expoting reuslt to the .txt file
    std::ofstream ofile;
    ofile.open("barrier.txt");

    ofile << "V matrix" <<std::endl;
    ofile << V <<std::endl;

    return 0;
}