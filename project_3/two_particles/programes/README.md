# All programmes had been written by Yevhenii Volkov


"partice.hpp" & "particle.cpp" files are the same files that defines and declares "particle" class as for 1 particle.



"trap.hpp" & "trap.cpp" files are files that defines and declares "trap" class. This class is updated. It has more fuctions, variables and contains RK4 & FE functions that can solve differential equatios for problem of 2 particles with & without particle interaction.


"2particles.cpp" is a .cpp programme that solves differential equation for 2 particles with FE & RK4 methods. This programme is used to generate "FE_table_2.csv", "FE_table_2_int.csv", "RK4_table_2.csv", "RK4_table_2_int.csv".


"xy_plot_2.py" is a python plotting scipt that takes "RK4_table_2.csv", "RK4_table_2_int.csv" tables as input. It had been used to create "xy_2_inter-.png", "xy_2_inter+.png" & "xy_2_subplot.png" figures.


"x_Vx_zVz_plot.py" is a python plotting scipt that takes "RK4_table_2.csv", "RK4_table_2_int.csv" tables as input. It had been used to create "x_Vx_inter-.png", "x_Vx_inter+.png", "x_Vx_subplot.png", "z_Vz_inter-.png", "z_Vz_inter+.png", "z_Vz_subplot.png" figures.


"xyz_plot_2.py" is a python plotting scipt that takes "RK4_table_2.csv", "RK4_table_2_int.csv" tables as input. It had been used to create "xy_inter-.png" & "xy_inter+.png" figures.
