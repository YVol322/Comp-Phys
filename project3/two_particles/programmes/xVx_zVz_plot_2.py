import csv
import numpy as np
from matplotlib import pyplot as plt 

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/two_particles/tables/RK4_table_2.csv")
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

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/two_particles/tables/RK4_table_2_int.csv")
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

plt.rcParams['font.size'] = '13'

plt.figure(1)
plt.xlabel('Coordinate $x [ \mu m]$')
plt.ylabel('Speed $V_x [ \mu m/ \mu s]$')
plt.plot(x1,vx1, label = "particle 1", linewidth = 1, color = "r")
plt.plot(x2,vx2, label = "particle 2", linewidth = 1, color = "k")
plt.title("$(x, V_x)$ plane without interaction")
plt.legend(fontsize = 12)


plt.figure(2)
plt.xlabel('Coordinate $x [ \mu m]$')
plt.ylabel('Speed $V_x [ \mu m/ \mu s]$')
plt.plot(x1_int,vx1_int, label = "particle 1", linewidth = 1, color = "r")
plt.plot(x2_int,vx2_int, label = "particle 2", linewidth = 1, color = "k")
plt.title("$(x, V_x)$ plane with interaction")
plt.legend(fontsize = 12)
plt.show()

plt.rcParams['font.size'] = '10'


fig, axs = plt.subplots(2)
axs[0].plot(x1_int,vx1_int, label = "particle 1", linewidth = 1, color = "r")
axs[0].plot(x2_int,vx2_int, label = "particle 2", linewidth = 1, color = "k")
axs[0].set_title('With interaction')
axs[0].set(ylabel = 'Speed $V_x [ \mu m/ \mu s]$')
axs[0].legend()
plt.legend(fontsize = 10)


axs[1].plot(x1,vx1, label = "particle 1", linewidth = 1, color = "r")
axs[1].plot(x2,vx2, label = "particle 2", linewidth = 1, color = "k")
axs[1].set_title('Without interaction', fontsize = 5)
plt.xlabel('Coordinate $x [ \mu m]$')
plt.ylabel('Speed $V_x [ \mu m/ \mu s]$')
axs[1].legend()
plt.show()

plt.rcParams['font.size'] = '10'

plt.figure(3)
plt.xlabel('Coordinate $z [ \mu m]$')
plt.ylabel('Speed $V_z [ \mu m/ \mu s]$')
plt.plot(z1,vz1, label = "particle 1", linewidth = 1.5, color = "r")
plt.plot(z2,vz2, label = "particle 2", linewidth = 1.5, color = "k")
plt.title("$(z, V_z)$ plane without interaction")
plt.legend(fontsize = 12)


plt.figure(4)
plt.xlabel('Coordinate $z [ \mu m]$')
plt.ylabel('Speed $V_z [ \mu m/ \mu s]$')
plt.plot(z1_int,vz1_int, label = "particle 1", linewidth = 0.5, color = "r")
plt.plot(z2_int,vz2_int, label = "particle 2", linewidth = 0.5, color = "k")
plt.title("$(z, V_z)$ plane with interaction")
plt.legend(fontsize = 12)
plt.show()

plt.rcParams['font.size'] = '10'


fig, axs = plt.subplots(2)
axs[0].plot(z1_int,vz1_int, label = "particle 1", linewidth = 0.5, color = "r")
axs[0].plot(z2_int,vz2_int, label = "particle 2", linewidth = 0.5, color = "k")
axs[0].set_title('With interaction')
axs[0].set(ylabel = 'Speed $V_z [ \mu m/ \mu s]$')
axs[0].legend()
plt.legend(fontsize = 10)


axs[1].plot(z1,vz1, label = "particle 1", linewidth = 0.5, color = "r")
axs[1].plot(z2,vz2, label = "particle 2", linewidth = 0.5, color = "k")
axs[1].set_title('Without interaction')
plt.xlabel('Coordinate $z [ \mu m]$')
plt.ylabel('Speed $V_z [ \mu m/ \mu s]$')
axs[1].legend()
plt.show()