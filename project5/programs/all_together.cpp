#include <iostream>
#include <armadillo>

//function that fills the potentail matrix and outputs it
arma::mat fill_V(double v_0, int M, double h);


//function that sets up the initial U matrix and oututs it
arma::cx_mat set_U(double x_c, double y_c, double s_x, double s_y, double p_x,
                double p_y, int M, double h);


//function that fills A matrix
arma::cx_mat fill_A_matrix(arma::cx_mat V, double dt, double h, int M);

//function that fills B matrix
arma::cx_mat fill_B_matrix(arma::cx_mat V, double dt, double h, int M);

//function that transforms indexes i,j into index k
int get_index(int i, int j, int M);

//function that computes solution of linear equation
arma::cx_vec solve_syst(arma::cx_mat A, arma::cx_mat B, arma::cx_vec u, int M);




int main ()
{
    int M = 100;    //number of points in x and y direction (including boundary)
    double h = 1./M;  //discrete step
    double dt = h; //time step
    int m = 10; //full number of time steps
    double T = m * dt; //full time of simulation

    //wave packet parameters according to the problem 8
    double x_c = 0.25;
    double y_c = 0;
    double s_x = 0.05;
    double s_y = 0.05;
    double p_x = 200;
    double p_y = 0;

    double v_0 = pow(10,10); //v_0


    //Step 1: filling the potential matrix

    arma::cx_mat V(M,M);   //potential matrix
    V.set_real(fill_V(v_0, M, h)); //setting real part to V

    arma::mat C(M,M, arma::fill::zeros); //setting im part to zeros
    V.set_imag(C);

    arma::cx_mat V2(M-2,M-2);   //V matrix of size ((M-2),(M-2))

    for(int i=0;i<M-2;i++)
    {
        for(int j=0;j<M-2;j++)
        {
            V2(i,j) = V(i+1,j+1);
        }
    }

    //Step 2: set up the initial state matrix

    arma::cx_mat U(M,M);    
    arma::cx_mat U2(M-2,M-2);   //V matrix of size ((M-2),(M-2))
    U = set_U(x_c, y_c, s_x, s_y,p_x, p_y, M, h);   //filling U matrix
    arma::cx_vec u((M-2) * (M-2));  //creating u vector

    for(int i=0;i<M-2;i++)
    {
        for(int j=0;j<M-2;j++)
        {
            u((M-2)*i +j) = U(j+1,i+1);     //filling u vector
            U2(j,i) = U(j+1,i+1); 
        }
    }

    //Step 3: set up A and B matrixes according to C-N approach

    arma::cx_mat A(M-2,M-2);
    A = fill_A_matrix(V2,dt,h,M-2);

    arma::cx_mat B(M-2,M-2);
    B = fill_B_matrix(V2,dt,h,M-2);

    //step 4: solve linear system for a time loop
    arma::cx_cube U_cube(M-2,M-2, m);

    arma::cx_vec u_new((M-2)*(M-2));

    U_cube.slice(0) = U2;

    for(int i=1;i<m;i++)
    {
        u_new = solve_syst(A,B,u, M-2);

        for(int j=0;j<M-2;j++)
        {
            for(int k=0;k<M-2;k++)
            {
                U_cube(j,k,i) = u_new((M-2)*j+k);
            }
        }
        u=u_new;
        std::cout << i <<std::endl;
    }
    
    std::string filename = "all_together_U.txt";    //expoting reuslt to the .txt file
    std::ofstream ofile;
    ofile.open("all_together_U.txt");
    ofile << "U^0, U^1, ..., U^9" << std::endl;

    for(int i=0; i<m;i++)
    {
        ofile << U_cube.slice(i) << std::endl;
    }



    return 0;
}

arma::mat fill_V(double v_0, int M, double h)
{
    double a = 0.02; //wall thickness
    double b = 0.05; // aperture & distanse between ends of the slits

    double a_points;
    double b_points;

    a_points = a/h; //wall thickness in terms of h
    b_points = b/h;  // aperture & distanse between ends of the slits in terms of h

    arma::mat V(M,M);   //potential matrix

    for(int i=0;i<=a_points;i++)
    {
        V.col((0.49 + i*h)/h).fill(v_0);
    }

    for(int j=0;j<=b_points;j++)
    {
        V.row((0.425 + j * h)/h).fill(0);
        V.row((0.525 + j * h)/h).fill(0);
    }

    //if(V(94,100)!=0)
    //{
    //    V.row(94).fill(0);
    //}

    return V;
}

arma::cx_mat set_U(double x_c, double y_c, double s_x, double s_y, double p_x,
                double p_y, int M, double h)
{
    arma::vec x(M);
    arma::vec y(M);

    arma::vec x_diff(M);
    arma::vec y_diff(M);

    //filling x-x_c, y-y_c vectors
    for(int i=0; i<M;i++)
    {
        x(i) = i*h;
        y(i) = i*h;

        x_diff(i) = x(i) - x_c;
        y_diff(i) = y(i) - y_c;
    }

    //computing U matrix
    arma::cx_mat U(M,M);

    for(int i=0;i<M;i++)
    {
        for(int j=0;j<M;j++)
        {
            double re = -x_diff(j)*x_diff(j)/(2*s_x*s_x) - y_diff(i)*y_diff(i)/(2*s_y*s_y);
            double im = p_x * x_diff(j) + p_y * y_diff(j);
            arma::cx_double p(re,im);

            U(j,i) = std::exp(p);
        }
    }

    //computing conj. matrix
    arma::cx_mat U_conj = arma::conj(U);

    //computing sum of U^*U
    arma::cx_double sum = arma::cx_double(0,0);

    for(int i=0;i<M;i++)
    {
        for(int j=0;j<M;j++)
        {
            sum += U(i,j) * U_conj(i,j);
        }
    }

    arma::cx_double sum_before = sum;
    

    //normalising U
    arma::cx_double norm = arma::cx_double(1./(sqrt(sum.real())),0);

    for(int i=0;i<M;i++)
    {
        for(int j=0;j<M;j++)
        {
            U(i,j) = U(i,j) * norm;
        }
    }

    U_conj = arma::conj(U);
    sum = arma::cx_double(0,0);

    for(int i=0;i<M;i++)
    {
        for(int j=0;j<M;j++)
        {
            sum += U(i,j) * U_conj(i,j);
        }
    }

    return U;
}

arma::cx_mat fill_A_matrix(arma::cx_mat V, double dt, double h, int M)
{
    arma::cx_mat A(M*M,M*M);       //A matrix
    arma::cx_vec a(M*M);       //diag vector

    arma::cx_double r = arma::cx_double(0, dt/(2*h*h));

    for(int i=0; i<M;i++)
    {
        a(i) = arma::cx_double(1,0) + arma::cx_double(4,0) * r + arma::cx_double(0,dt/2) * V(i,i);
    }

    A.diag() = a;   //setting diagonal elements to vector a
    A.diag(-3).fill(-r);    //filling -1,1,-3,3 diagonals with -r
    A.diag(3).fill(-r);
    A.diag(-1).fill(-r);
    A.diag(1).fill(-r);


    //setting every Mth element on 3 and -3 diagonals to zeros
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
    arma::cx_vec b = arma::cx_vec(M*M);

    arma::cx_double r = arma::cx_double(0, dt/(2*h*h));

    for(int i=0; i<M;i++)
    {
        b(i) = arma::cx_double(1,0) - arma::cx_double(4,0) - r + arma::cx_double(0,dt/2) * V(i,i);
    }

    B.diag() = b;   //setting diagonal elements to vector a
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

arma::cx_vec solve_syst(arma::cx_mat A, arma::cx_mat B, arma::cx_vec u, int M)
{
    arma::cx_vec b(M*M);    //vecor result of multiolying A*u

    b = A * u;

    arma::cx_vec x(M*M);    //solution of a linear system vector

    x = arma::solve(A, b);  //using built-in arma solver

    return x;
}