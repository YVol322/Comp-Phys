import csv
import numpy as np
from matplotlib import pyplot as plt

file = open("/Users/JVol/Documents/GitHub/comp-phys/project_4/2x2table.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
T = []
an_eps = []
an_eps_2 = []
an_m = []
an_m_2 = []
an_C_v = []
an_Chi = []
pr_eps = []
pr_eps_2 = []
pr_m = []
pr_m_2 = []
pr_C_v = []
pr_Chi = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    T.append(float(rows[i][0].strip()))
    an_eps.append(float(rows[i][1].strip()))
    an_eps_2.append(float(rows[i][2].strip()))
    an_m.append(float(rows[i][3].strip()))
    an_m_2.append(float(rows[i][4].strip()))
    an_C_v.append(float(rows[i][5].strip()))
    an_Chi.append(float(rows[i][6].strip()))
    pr_eps.append(float(rows[i][7].strip()))
    pr_eps_2.append(float(rows[i][8].strip()))
    pr_m.append(float(rows[i][9].strip()))
    pr_m_2.append(float(rows[i][10].strip()))
    pr_C_v.append(float(rows[i][11].strip()))
    pr_Chi.append(float(rows[i][12].strip()))

file.close()


plt.figure(1)
plt.plot(T,an_eps, label = "analytical <$\epsilon$>")
plt.plot(T, pr_eps, label = "computed <$\epsilon$>")
plt.xlabel('$T$, $ J$ \ $k_B$')
plt.ylabel('$<\epsilon>$, $\ J$')
plt.legend()
plt.show()

plt.figure(2)
plt.plot(T,an_eps_2, label = "analytical <$\epsilon^2$>")
plt.plot(T, pr_eps_2, label = "computed <$\epsilon^2$>")
plt.xlabel('$T$, $ J$ \ $k_B$')
plt.ylabel('$<\epsilon^2>$, $\ J^2$')
plt.legend()
plt.show()

plt.figure(3)
plt.plot(T,an_m, label = "analytical <$m$>")
plt.plot(T, pr_m, label = "computed <$m$>")
plt.xlabel('$T$, $ J$ \ $k_B$')
plt.ylabel('$<|m|>$')
plt.legend()
plt.show()

plt.figure(4)
plt.plot(T,an_m_2, label = "analytical <$m^2$>")
plt.plot(T, pr_m_2, label = "computed <$m^2$>")
plt.xlabel('$T$, $ J$ \ $k_B$')
plt.ylabel('$<m^2>$')
plt.legend()
plt.show()

plt.figure(5)
plt.plot(T,an_C_v, label = "analytical $C_v$")
plt.plot(T, pr_C_v, label = "computed $C_v$")
plt.xlabel('$T$, $ J$ \ $k_B$')
plt.ylabel('$C_V$, $k_B$')
plt.legend()
plt.show()

plt.figure(6)
plt.plot(T,an_Chi, label = "analytical $\chi$")
plt.plot(T, pr_Chi, label = "computed $\chi$")
plt.xlabel('$T$, $ J$ \ $k_B$')
plt.ylabel('$\chi$, $J^{-1}$')
plt.legend()
plt.show()
