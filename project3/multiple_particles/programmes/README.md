# All programmes had been written by Yevhenii Volkov


"particle.hpp" & "particles.cpp" are the same "particle" class files.


"trap.hpp" & "trap.cpp" are the modified "trap class" files. Updated class has function that can implement RK4, F3 methods for $n$ particle with and without interactions.


"100particles.cpp" is the .cpp programme that implements RK4 method for solving 100 particles probleme without interaction for time dependent electric potetial $V(t)$ with different amplidules $f$ and angular frequences $\omega_v$. This programme had been used to generate "RK4_table_500ms_100p.csv" & "RK4_table_500ms_100p_reso.csv" tables.


"inter100particles.cpp" is the .cpp programme that implements RK4 method for solving 25 particles (due to time saving, programme for 25 particles had been working for 30 miutes) probleme with & without interaction for time dependent electric potetial $V(t)$ with different amplidules $f$ and angular frequences $\omega_v$. This programme had been used to generate "RK4_table_500ms_25p_reso_int.csv" & "RK4_table_500ms_25p_reso.csv" tables.


"RK4_100p_25p_plot.py" is the python plotting script that had built all figures from "figures" folder.
