import csv
import numpy as np
from matplotlib import pyplot as plt

file = open("/Users/JVol/Documents/GitHub/comp-phys/project_4/20x20_table_+1.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
N = []
eps_1 = []
m_1 = []
eps_24 = []
m_24 = []


for row in csvreader:
    rows.append(row)

print(len(rows))
for i in range(0,79999,1):
    N.append(float(rows[i][0].strip()))
    eps_1.append(float(rows[i][1].strip()))
    m_1.append(float(rows[i][2].strip()))

for i in range(80000,159999,1):
    eps_24.append(float(rows[i][1].strip()))
    m_24.append(float(rows[i][2].strip()))


file.close()



plt.figure(1)
plt.plot(N,eps_1, label = "$T=1$ [$J$]")
plt.plot(N,eps_24, label = "$T=2.4$ [$J$]", linestyle = 'dashed')
plt.xlabel('Number of MCMC cycles $N$')
plt.ylabel('Mean energy per spin $<\epsilon>$, $\ J$')
plt.legend()
plt.show()

plt.figure(2)
plt.plot(N,m_1, label = "$T=1$ [$J$]")
plt.plot(N,m_24, label = "$T=2.4$ [$J$]", linestyle = 'dashed')
plt.xlabel('Number of MCMC cycles $N$')
plt.ylabel('Mean magnetization per spin $<|m|>$')
plt.legend()
plt.show()