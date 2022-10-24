#include <iostream>
#include <armadillo>

int main()
{
    double z0 = 20;
    double x0 = 20;
    double v0 = 25;

    double q = 1;
    double m = 40.078;
    double B = 96.5;
    double V = 2.41 * pow(10, 6);
    double d = 500;

    double Wz = 2 * q * V/(m * pow(d,2));
    double W0 = q * B/ m;

    double W1 = (W0 + sqrt(pow(W0,2) - 2 * Wz))/2;
    double W2 = (W0 - sqrt(pow(W0,2) - 2 * Wz))/2;
    double A1 = (v0 + W2*x0)/(W2-W1);
    double A2 = -(v0 + W1*x0)/(W2-W1);

    double t = 50.;
    double n = 4000.;
    double h = t/n;

    arma::vec x(n+1), y(n+1), z(n+1), time(n+1);
    x(0) = x0;
    y(0) = 0;
    z(0) = z0;
    time(0) = 0;

    for(int i; i<n; i++)
    {
        double b = h * i;

        z(i+1) = z0 * cos(sqrt(Wz) * b);
        x(i+1) = A1 * cos(W1 * b) + A2 * cos(W2 * b);
        y(i+1) = -A1 * sin(W1 * b) - A2 * sin(W2 * b);
        time(i+1) = (b+1);
    }

    std::string filename = "analyt_sol_4k.csv";
    std::ofstream ofile;
    ofile.open("analyt_sol_4k.csv"); 

    ofile <<"x[μm], y[μm], z[μm], t[μm]"<<std::endl;

    int width = 15;
    int prec  = 6;

    for(int i=0; i<n;i++)
    {
        ofile << std::setw(width) << std::setprecision(prec) << std::scientific << x(i) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << y(i) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << z(i) << ","
        << std::setw(width) << std::setprecision(prec) << std::scientific << time(i) << std::endl; 
    }


    return 0;
}