import csv
import numpy as np
from matplotlib import pyplot as plt 

file = open("/Users/JVol/Documents/GitHub/comp-phys/project2/pr5table.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
N = []
j = []
for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    N.append(float(rows[i][0].strip()))
    j.append(float(rows[i][1].strip()))

f2 = np.polyfit(N,j, 2)


plt.title("Number of itereations VS Number of rows/cos of A/R matrix for Jacobi's rotation algo")
plt.xlabel("Numer of rows of A matrix N")
plt.ylabel("Number of iterations J")
plt.plot(N,j, "ob", label = "exact solutions")
plt.plot(np.polyval(f2, N), label = "2nd order polynomial approximation")

plt.legend()
plt.show()