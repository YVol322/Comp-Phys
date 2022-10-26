import csv
from math import log
from turtle import title
import numpy as np
from matplotlib import pyplot as plt 

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/single_particle/RK4_sol_4k.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
x4 = []
y4 = []
z4 = []
t4 = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    x4.append(float(rows[i][0].strip()))
    y4.append(float(rows[i][1].strip()))
    z4.append(float(rows[i][2].strip()))
    t4.append(float(rows[i][3].strip()))

file.close()

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/single_particle/analyt_sol_4k.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
xa4 = []
ya4 = []
za4 = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    xa4.append(float(rows[i][0].strip()))
    ya4.append(float(rows[i][1].strip()))
    za4.append(float(rows[i][2].strip()))

file.close()

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/single_particle/RK4_sol_8k.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
x8 = []
y8 = []
z8 = []
t8 = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    x8.append(float(rows[i][0].strip()))
    y8.append(float(rows[i][1].strip()))
    z8.append(float(rows[i][2].strip()))
    t8.append(float(rows[i][3].strip()))

file.close()

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/single_particle/analyt_sol_8k.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
xa8 = []
ya8 = []
za8 = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    xa8.append(float(rows[i][0].strip()))
    ya8.append(float(rows[i][1].strip()))
    za8.append(float(rows[i][2].strip()))

file.close()

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/single_particle/RK4_sol_16k.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
x16 = []
y16 = []
z16 = []
t16 = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    x16.append(float(rows[i][0].strip()))
    y16.append(float(rows[i][1].strip()))
    z16.append(float(rows[i][2].strip()))
    t16.append(float(rows[i][3].strip()))

file.close()

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/single_particle/analyt_sol_16k.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
xa16 = []
ya16 = []
za16 = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    xa16.append(float(rows[i][0].strip()))
    ya16.append(float(rows[i][1].strip()))
    za16.append(float(rows[i][2].strip()))

file.close()

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/single_particle/RK4_sol_32k.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
x32 = []
y32 = []
z32 = []
t32 = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    x32.append(float(rows[i][0].strip()))
    y32.append(float(rows[i][1].strip()))
    z32.append(float(rows[i][2].strip()))
    t32.append(float(rows[i][3].strip()))

file.close()

file = open("/Users/JVol/Documents/GitHub/comp-phys/project3/single_particle/analyt_sol_32k.csv")
type(file)
csvreader=csv.reader(file)
header = []
header = next(csvreader)
rows = []
xa32 = []
ya32 = []
za32 = []

for row in csvreader:
    rows.append(row)

for i in range(len(rows)):
    xa32.append(float(rows[i][0].strip()))
    ya32.append(float(rows[i][1].strip()))
    za32.append(float(rows[i][2].strip()))

file.close()

rx4 = []
rx8 = []
rx16 = []
rx32 = []

d4 = []
d8 = []
d16 = []
d32 = []

for i in range(len(x4)):
    rx4.append(abs(x4[i]-xa4[i])/xa4[0])
    d4.append(abs(x4[i]-xa4[i]))


for i in range(len(x8)):
    rx8.append(abs(x8[i]-xa8[i])/xa8[0])
    d8.append(abs(x8[i]-xa8[i]))

for i in range(len(x16)):
    rx16.append(abs(x16[i]-xa16[i])/xa16[0])
    d16.append(abs(x16[i]-xa16[i]))

for i in range(len(x32)):
    rx32.append(abs(x32[i]-xa32[i])/xa32[0])
    d32.append(abs(x32[i]-xa32[i]))


fig, axs = plt.subplots(2, 2)
axs[0, 0].plot(t4, rx4)
axs[0, 0].set_title('$n=4000$')
axs[0, 1].plot(t8, rx8)
axs[0, 1].set_title('$n=8000$')
axs[1, 0].plot(t16, rx16)
axs[1, 0].set_title('$n=16000$')
axs[1, 1].plot(t32, rx32)
axs[1, 1].set_title('$n=32000$')

delta = []
delta.append(max(d4))
delta.append(max(d8))
delta.append(max(d16))
delta.append(max(d32))

h =[(float(50)/4000), (float(50)/8000), (float(50)/16000), (float(50)/32000)]

r_err1 = log(delta[1]/delta[1-1])/log(h[1]/h[1-1])
r_err2 = log(delta[2]/delta[2-1])/log(h[2]/h[2-1])
r_err3 = log(delta[3]/delta[3-1])/log(h[3]/h[3-1])

r_err = float(1)/3 * (r_err1+r_err2+r_err3)
print(r_err)