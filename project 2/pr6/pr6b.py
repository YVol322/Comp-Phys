import csv
import numpy as np
from matplotlib import pyplot as plt 

file = open("/Users/JVol/Documents/GitHub/comp-phys/project 2/pr6/pr6btable.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
x = []
v0 = []
v1 = []
v2 = []
u0 = []
u1 = []
u2 = []
for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    x.append(float(rows[i][0].strip()))
    v0.append(float(rows[i][1].strip()))
    v1.append(float(rows[i][2].strip()))
    v2.append(float(rows[i][3].strip()))
    u0.append(float(rows[i][4].strip()))
    u1.append(float(rows[i][5].strip()))
    u2.append(float(rows[i][6].strip()))

#if we want to invert vec uj

#for i in range(101):
#    u2[i] = -u2[i]


plt.title("Jac./Analyt. sol. of dif. eq. v/u vs dimless. beam coordinate x. N = 100")
plt.xlabel("Dimensionless beam coordinate x")
plt.ylabel("Jacobi's method/analytical solution of dif. eq. v/u")

plt.plot(x, v0, linestyle='dashed', linewidth=1, color = "r", label = "1st Jacobi's eigval")
plt.plot(x, u0, linestyle='dashed', linewidth=1, color = "b", label = "1st analytical eigval")
plt.plot(x, v1, linestyle='dashed', linewidth=1, color = "r", label = "2nd Jacobi's eigval")
plt.plot(x, u1, linestyle='dashed', linewidth=1, color = "b", label = "2nd analytical eigval")
plt.plot(x, v2, linestyle='dashed', linewidth=1, color = "r", label = "3rd Jacobi's eigval")
plt.plot(x, u2, linestyle='dashed', linewidth=1, color = "b", label = "3rd analytical eigval")


plt.legend()
plt.show()