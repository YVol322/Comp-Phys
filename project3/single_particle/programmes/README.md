"particle.hpp" is a header file for "particle" class. Here we define the constructor, this file does not have any functions. It takes charge $q$, mass $m$, coordinate $\vec{r}$ & velocity $\vec{v}$ of particle as input


"particle.cpp" is a .cpp file for "particle" class with constructor only.


"trap.hpp" is a header file for "trap" class. Here we define the constructor and few functions needed to solve tasks with one particle.


"trap.cpp" is a .cpp file for "trap" class. Here we declare constructor & functions. In this file declared Forward Eurel & Runge Kutta 4th order method. In folders "two_particles", "multiple_particles" this class .hpp & .cpp files are modified in case to be able to solve more complex tasks.


"1particle.cpp" is a .cpp programme that implements FE, RK4 methods to 1 particle problem. This programme was used to generate "FE_sol_4k.csv", "FE_sol_8k.csv", "FE_sol_16k.csv", "FE_sol_32k.csv", "RK4_sol_4k.csv", "RK4_sol_8k.csv", "RK4_sol_16k.csv", "RK4_sol_32k.csv", "RK4_table.csv" tables.


"analyt_sol_1.cpp" is a .cpp programme that evaluates analytical solution of Newton's equation. This programme was used to generate "analyt_sol_4k.csv", "analyt_sol_8k.csv", "analyt_sol_16k.csv", "analyt_sol_32k.csv" tables.


"RK4_1particle_plotscript_16k.py" is a python plotting script that takes "RK4_table.csv" as input and generates some figures. This programme was used to build "z_vs_t_16k_RK4.png" figure.


"RK4_vs_analyt.py" is python programme that takes all the tables (without "RK4_table.csv") as input and generate error figures & calculates error convergence rate for FE, RK4 methods. This programme was used to build "FE_analyt.png" & "RK4_analyt.png" figures. The figures shows not relative error, but absolute error divided by absolute value of initial value (because of division to zero error).
