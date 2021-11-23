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
sampleStart = 32867
L1 = 360*15


plt.figure(4)
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,x106[sampleStart:sampleStart+L1],'b-')
plt.xlabel('Time (Sec)')
plt.ylabel('Amplitude')
plt.grid(True)
plt.title('ECG of Premature Ventricular Beats (At sample 33653)')


plt.figure(5)
sampleStart = 33045
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,x106[sampleStart:sampleStart+L1],'b-')
plt.xlabel('Time (Sec)')
plt.ylabel('Amplitude')
plt.grid(True)
plt.title('ECG of Premature Ventricular Beats (At sample 35468)')

plt.figure(6)
sampleStart = 33820
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,x106[sampleStart:sampleStart+L1],'b-')
plt.xlabel('Time (Sec)')
plt.ylabel('Amplitude')
plt.grid(True)
plt.title('ECG of Premature Ventricular Beats (At sample 37123)')


plt.show()