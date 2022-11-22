import csv
import numpy as np
from matplotlib import pyplot as plt

file = open("/Users/JVol/Documents/GitHub/comp-phys/project_4/20x20_table_hist.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
N = []
eps_1 = []
eps_24 = []

N =400
n= 10000

for row in csvreader:
    rows.append(row)


for i in range(0,n*N-1,1):
    eps_1.append(float(rows[i][1].strip()))

for i in range(n*N,2*n*N-1,1):
    eps_24.append(float(rows[i][1].strip()))


file.close()

max1 = max(eps_1)
max2 = max(eps_24)

bin = np.arange(-0.4,0.4,0.02)

#plt.figure(1)
#plt.hist(eps_1, bins=bin, range=[-0.5,0.5], density=False)
#plt.xlabel('$\epsilon$, [$J$]')
#plt.ylabel('number of times that the values occurred out of $N\cdot n = 4\cdot 10^{6}$')
#plt.show()
#plt.figure(2)
#plt.hist(eps_24, bins=bin, range=[-0.5,0.5], density=False)
#plt.xlabel('$\epsilon$')
#plt.ylabel('number of times that the values occurred out of $N\cdot n = 4\cdot 10^{6}$')
#plt.show()
plt.figure(2)
plt.hist(eps_1, bins=bin, range=[-0.5,0.5], density=False, color='k', label='T=1 [$J$ / $k_B$]')
plt.hist(eps_24, bins=bin, range=[-0.5,0.5], density=False, label='T=2.4 [$J$ / $k_B$]')
plt.xlabel('$\epsilon$')
plt.ylabel('number of times that the values occurred out of $N\cdot n = 4\cdot 10^{6}$')
plt.legend()
plt.show()