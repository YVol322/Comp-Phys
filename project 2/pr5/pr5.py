import csv
import numpy as np
from matplotlib import pyplot as plt 

file = open("/Users/JVol/Documents/GitHub/comp-phys/project 2/pr5/pr5btable.csv")
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
    N[i] =N[i] - 4

f2 = np.polyfit(N,j, 2)
print(f2)


plt.title("Dense A matrix")
plt.xlabel("Numer of rows of A matrix (N-4)")
plt.ylabel("Number of iterations j")
plt.plot(N,j, "ob", label = "exact solutions")
plt.plot(np.polyval(f2, N), label = "2nd order polynomial approximation")

plt.legend()
plt.show()