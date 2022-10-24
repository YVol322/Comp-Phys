from cProfile import label
import csv
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D



file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/two_particles/RK4_table_2.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
x1 = []
y1 = []
z1 = []
vx1 = []
vy1 = []
vz1 = []
x2 = []
y2 = []
z2 = []
vx2 = []
vy2 = []
vz2 = []
t = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    x1.append(float(rows[i][0].strip()))
    y1.append(float(rows[i][1].strip()))
    z1.append(float(rows[i][2].strip()))
    vx1.append(float(rows[i][3].strip()))
    vy1.append(float(rows[i][4].strip()))
    vz1.append(float(rows[i][5].strip()))
    x2.append(float(rows[i][6].strip()))
    y2.append(float(rows[i][7].strip()))
    z2.append(float(rows[i][8].strip()))
    vx2.append(float(rows[i][9].strip()))
    vy2.append(float(rows[i][10].strip()))
    vz2.append(float(rows[i][11].strip()))
    t.append(float(rows[i][12].strip()))

file.close()

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/two_particles/RK4_table_2_int.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
x1_int = []
y1_int = []
z1_int = []
vx1_int = []
vy1_int = []
vz1_int = []
x2_int = []
y2_int = []
z2_int = []
vx2_int = []
vy2_int = []
vz2_int = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    x1_int.append(float(rows[i][0].strip()))
    y1_int.append(float(rows[i][1].strip()))
    z1_int.append(float(rows[i][2].strip()))
    vx1_int.append(float(rows[i][3].strip()))
    vy1_int.append(float(rows[i][4].strip()))
    vz1_int.append(float(rows[i][5].strip()))
    x2_int.append(float(rows[i][6].strip()))
    y2_int.append(float(rows[i][7].strip()))
    z2_int.append(float(rows[i][8].strip()))
    vx2_int.append(float(rows[i][9].strip()))
    vy2_int.append(float(rows[i][10].strip()))
    vz2_int.append(float(rows[i][11].strip()))

file.close()

fig1 = plt.figure()
ax1 = plt.axes(projection='3d')
ax1.plot3D(x1, y1, z1, 'r')
ax1.plot3D(x2, y2, z2, 'k', linestyle = "--")

fig2 = plt.figure()
ax2 = plt.axes(projection='3d')
ax2.plot3D(x1_int, y1_int, z1_int, 'r')
ax2.plot3D(x2_int, y2_int, z2_int, 'k', linestyle = "--")
plt.show()