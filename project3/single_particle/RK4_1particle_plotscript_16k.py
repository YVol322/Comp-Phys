import csv
import numpy as np
from matplotlib import pyplot as plt 

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/single_particle/RK4_table.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
x = []
y = []
z = []
vx = []
vy = []
vz = []
t = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    x.append(float(rows[i][0].strip()))
    y.append(float(rows[i][1].strip()))
    z.append(float(rows[i][2].strip()))
    vx.append(float(rows[i][3].strip()))
    vy.append(float(rows[i][4].strip()))
    vz.append(float(rows[i][5].strip()))
    t.append(float(rows[i][6].strip()))

plt.rcParams['font.size'] = '16'

plt.figure(1)
plt.xlabel('Coordinate $z [ \mu m]$')
plt.ylabel('Time $t [ \mu s]$')
plt.plot(t,z, label = "RK4 solution", linewidth = 2, color = "r")
plt.legend()

plt.figure(2)
plt.xlabel('Coordinate $x [ \mu m]$')
plt.ylabel('Time $t [ \mu s]$')
plt.plot(t,x, label = "RK4 solution", linewidth = 2, color = "r")
plt.legend()

plt.figure(3)
plt.xlabel('Coordinate $y [ \mu m]$')
plt.ylabel('Time $t [ \mu s]$')
plt.plot(t,y, label = "RK4 solution", linewidth = 2, color = "r")
plt.legend()

plt.figure(4)
plt.xlabel('Speed $V_x [ \mu m]$')
plt.ylabel('Time $t [ \mu s]$')
plt.plot(t,vx, label = "RK4 solution", linewidth = 2, color = "r")
plt.legend()

plt.figure(5)
plt.xlabel('Speed $V_y [ \mu m]$')
plt.ylabel('Time $t [ \mu s]$')
plt.plot(t,vy, label = "RK4 solution", linewidth = 2, color = "r")
plt.legend()

plt.figure(6)
plt.xlabel('Speed $V_z [ \mu m]$')
plt.ylabel('Time $t [ \mu s]$')
plt.plot(t,vz, label = "RK4 solution", linewidth = 2, color = "r")
plt.legend()
plt.show()