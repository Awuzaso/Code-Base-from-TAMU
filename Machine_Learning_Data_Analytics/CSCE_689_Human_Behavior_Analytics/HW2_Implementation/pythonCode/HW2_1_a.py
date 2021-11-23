# Import necessary libraries.
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

# a) Visualization of ECG components
    # 1) Select adnd plot examples of ECG signals containing normal beats with duration of 10-20 sec.
    # 2) Please note the three main ECG components:
        # a) P wave
        # b) QRS complex
        # c) T wave

x106 = np.loadtxt("/Users/awuzaso/Documents/codingProjects/Tutorial1/MitArrhythmia/Data/106.txt")

Fs = 360
L=20

firstSec = 360
secSec = 360*2

sampleStart = 83
L1 = 360*15


plt.figure(1)
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,x106[sampleStart:sampleStart+L1],'b-')
plt.xlabel('Time (Sec)')
plt.ylabel('Amplitude')
'''
plt.text(0.85,1026.9,"P-wave")
plt.text(0.99,1422,"QRS-Complex")
plt.text(1.13,1042,"T-wave")
'''
plt.grid(True)
plt.title('ECG of Normal Beats')


plt.figure(2)
sampleStart = 8475
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,x106[sampleStart:sampleStart+L1],'b-')
plt.xlabel('Time (Sec)')
plt.ylabel('Amplitude')
plt.grid(True)
plt.title('ECG of Normal Beats')

plt.figure(3)
sampleStart = 9769
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,x106[sampleStart:sampleStart+L1],'b-')
plt.xlabel('Time (Sec)')
plt.ylabel('Amplitude')
plt.grid(True)
plt.title('ECG of Normal Beats')

plt.show()