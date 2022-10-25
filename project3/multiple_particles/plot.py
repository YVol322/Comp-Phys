import csv
from re import X
import numpy as np
from matplotlib import pyplot as plt 

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/multiple_particles/RK4_table_500ms_100p.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
n1 = []
n2 = []
n3 = []
w = []


for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    n1.append(float(rows[i][0].strip()))
    n2.append(float(rows[i][1].strip()))
    n3.append(float(rows[i][2].strip()))
    w.append(float(rows[i][3].strip()))

plt.rcParams['font.size'] = '16'

plt.figure(1)
plt.xlabel('Time $t [ \mu s]$')
plt.axis([0.2, 2.5, -3, 102])
plt.ylabel('Coordinate $z [ \mu m]$')
plt.plot(w,n1,"ob",label = "RK4 solution", linewidth = 2, color = "r")

plt.figure(2)
plt.xlabel('Time $t [ \mu s]$')
plt.axis([0.2, 2.5, -3, 102])
plt.ylabel('Coordinate $x [ \mu m]$')
plt.plot(w,n2, "ob", label = "RK4 solution", linewidth = 2, color = "r")

plt.figure(3)
plt.xlabel('Time $t [ \mu s]$')
plt.axis([0.2, 2.5, -3, 102])
plt.ylabel('Coordinate $y [ \mu m]$')
plt.plot(w,n3, "ob", label = "RK4 solution", linewidth = 2, color = "r")

plt.show()