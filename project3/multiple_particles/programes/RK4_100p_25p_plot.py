import csv
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


file.close()


file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/multiple_particles/RK4_table_500ms_100p_reso.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
nr1 = []
nr2 = []
nr3 = []
wr = []


for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    nr1.append(float(rows[i][0].strip()))
    nr2.append(float(rows[i][1].strip()))
    nr3.append(float(rows[i][2].strip()))
    wr.append(float(rows[i][3].strip()))


file.close()


file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/multiple_particles/RK4_table_500ms_25p_reso.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
nr25_1 = []
nr25_2 = []
nr25_3 = []


for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    nr25_1.append(float(rows[i][0].strip()))
    nr25_2.append(float(rows[i][1].strip()))
    nr25_3.append(float(rows[i][2].strip()))


file.close()


file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/multiple_particles/RK4_table_500ms_25p_reso_int.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
nr25int_1 = []
nr25int_2 = []
nr25int_3 = []


for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    nr25int_1.append(float(rows[i][0].strip()))
    nr25int_2.append(float(rows[i][1].strip()))
    nr25int_3.append(float(rows[i][2].strip()))



plt.rcParams['font.size'] = '16'

plt.subplot(3, 1, 1)
plt.axis([0.2, 2.5, -3, 102])
plt.plot(w,n1,"ob",label = "$f=0.1$", linewidth = 2, color = "r")
plt.legend(fontsize = 10)


plt.subplot(3, 1, 2)
plt.ylabel('Number of tradped particles $n$')
plt.axis([0.2, 2.5, -3, 102])
plt.plot(w,n2,"ob",label = "$f=0.4$", linewidth = 2, color = "k")
plt.legend(fontsize = 10)


plt.subplot(3, 1, 3)
plt.axis([0.2, 2.5, -3, 102])
plt.plot(w,n3,"ob",label = "$f=0.7$", linewidth = 2, color = "g")
plt.xlabel('Angular frequency $\omega_v [ MHz]$')
plt.legend(fontsize = 10)
plt.show()

plt.figure(4)
plt.axis([0.2, 2.5, -3, 102])
plt.plot(w,n1,"ob",label = "$f=0.1$", linewidth = 2, color = "r")
plt.plot(w,n2,"ob",label = "$f=0.4$", linewidth = 2, color = "k")
plt.plot(w,n3,"ob",label = "$f=0.7$", linewidth = 2, color = "g")
plt.xlabel('Angular frequency $\omega_v [ MHz]$')
plt.ylabel('Number of tradped particles $n$')
plt.legend(fontsize = 10)

plt.subplot(3, 1, 1)
plt.axis([0.9, 1.8, -3, 27])
plt.plot(wr,nr25_1,"ob",label = "$f=0.1$", linewidth = 2, color = "r")
plt.legend(fontsize = 10)

plt.subplot(3, 1, 2)
plt.axis([0.9, 1.8, -3, 27])
plt.ylabel('Number of tradped particles $n$')
plt.plot(wr,nr25_2,"ob",label = "$f=0.4$", linewidth = 2, color = "k")
plt.legend(fontsize = 10)

plt.subplot(3, 1, 3)
plt.axis([0.9, 1.8, -3, 27])
plt.plot(wr,nr25_3,"ob",label = "$f=0.7$", linewidth = 2, color = "g")
plt.legend(fontsize = 10)
plt.xlabel('Angular frequency $\omega_v [ MHz]$')
plt.show()

plt.figure(5)
plt.axis([0.9, 1.8, -3, 27])
plt.plot(wr,nr25_1,"ob",label = "$f=0.1$", linewidth = 2, color = "r")
plt.plot(wr,nr25_2,"ob",label = "$f=0.4$", linewidth = 2, color = "k")
plt.plot(wr,nr25_3,"ob",label = "$f=0.7$", linewidth = 2, color = "g")
plt.xlabel('Angular frequency $\omega_v [ MHz]$')
plt.ylabel('Number of tradped particles $n$')
plt.legend(fontsize = 10)


plt.subplot(3, 1, 1)
plt.axis([0.9, 1.8, -3, 27])
plt.plot(wr,nr25int_1,"ob",label = "$f=0.1$", linewidth = 2, color = "r")
plt.legend(fontsize = 10)

plt.subplot(3, 1, 2)
plt.axis([0.9, 1.8, -3, 27])
plt.ylabel('Number of tradped particles $n$')
plt.plot(wr,nr25int_2,"ob",label = "$f=0.4$", linewidth = 2, color = "k")
plt.legend(fontsize = 10)

plt.subplot(3, 1, 3)
plt.axis([0.9, 1.8, -3, 27])
plt.plot(wr,nr25int_3,"ob",label = "$f=0.7$", linewidth = 2, color = "g")
plt.legend(fontsize = 10)
plt.xlabel('Angular frequency $\omega_v [ MHz]$')
plt.show()

plt.figure(6)
plt.axis([0.9, 1.8, -3, 27])
plt.plot(wr,nr25int_1,"ob",label = "$f=0.1$", linewidth = 2, color = "r")
plt.plot(wr,nr25int_2,'ob',label = "$f=0.4$", linewidth = 2, color = "k")
plt.plot(wr,nr25int_3,'ob',label = "$f=0.7$", linewidth = 2, color = "g")
plt.xlabel('Angular frequency $\omega_v [ MHz]$')
plt.ylabel('Number of tradped particles $n$')
plt.legend(fontsize = 10)


plt.figure(7)
plt.axis([0.9, 1.8, -3, 27])
plt.xlabel('Angular frequency $\omega_v [ MHz]$')
plt.ylabel('Number of tradped particles $n$')
plt.plot(wr,nr25_1,"ob",label = "$f=0.1$", linewidth = 1, color = "k")
plt.plot(wr,nr25int_1,"*",label = "$f=0.1$", linewidth = 2, color = "r")
plt.legend(fontsize = 10)


plt.figure(8)
plt.axis([0.9, 1.8, -3, 27])
plt.xlabel('Angular frequency $\omega_v [ MHz]$')
plt.ylabel('Number of tradped particles $n$')
plt.plot(wr,nr25_2,"ob",label = "$f=0.4$", linewidth = 1, color = "k")
plt.plot(wr,nr25int_2,"*",label = "$f=0.4$", linewidth = 2, color = "r")
plt.legend(fontsize = 10)


plt.figure(9)
plt.axis([0.9, 1.8, -3, 27])
plt.xlabel('Angular frequency $\omega_v [ MHz]$')
plt.ylabel('Number of tradped particles $n$')
plt.plot(wr,nr25_3,"ob",label = "$f=0.7$", linewidth = 1, color = "k")
plt.plot(wr,nr25int_3,"*",label = "$f=0.7$", linewidth = 2, color = "r")
plt.legend(fontsize = 10)
plt.show()