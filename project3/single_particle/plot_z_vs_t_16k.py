import csv
import numpy as np
from matplotlib import pyplot as plt 

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/single_particle/z_vs_t_16k_table.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
z = []
t = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    z.append(float(rows[i][0].strip()))
    t.append(float(rows[i][1].strip()))

plt.rcParams['font.size'] = '16'
plt.xlabel('Coordinate $z [ \mu m]$')
plt.ylabel('Time $t [ \mu s]$')
plt.plot(t,z, label = "RK4 solution", linewidth = 2, color = "r")
plt.legend()
plt.show()