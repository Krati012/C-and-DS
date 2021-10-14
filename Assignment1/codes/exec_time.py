import os
import subprocess
import matplotlib.pyplot as plt
import math
from scipy.optimize import curve_fit

#code for plotting runtime
ns = []
t1 = []
t2 = []
t3 = []
  
f = open('sample_data/runtime.txt','r')

for row in f:
    row = row.split(' ')
    ns.append(int(row[0]))
    t1.append(float(row[1]))
    t2.append(float(row[2]))
  
#objective function would be a + b*(n^2)
def objective(x, a, b):
    return a + b*np.square(x)

plt.figure()
#plt.plot(ns, t1, color = 'y')
plt.plot(ns, t2, color = 'r', label='Original execution time')
popt, pcov = curve_fit(objective, ns, t2)
print("For the equation a+b*(n^2), a: ", popt[0], " b:", popt[1])        
plt.plot(ns, objective(ns, *popt), color = 'g', marker=',', label='Fitted Curve %.8f + %.16f * n^2' % (popt[0],popt[1]))
plt.legend()	
plt.xlabel('n') 
plt.ylabel('Time(s)')
plt.show()
