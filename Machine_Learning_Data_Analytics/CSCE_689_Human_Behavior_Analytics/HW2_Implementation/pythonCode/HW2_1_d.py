# Import necessary libraries.
import numpy as np
import matplotlib.pyplot as plt
import scipy as sp
from scipy import signal
from scipy.fftpack import fft, rfft

'''
d) ECG feature extraction: 

	i) Segment the ECG signals into 5 sec analysis frames.
	ii) Using the annotation files in folder Annotations_NormalAbnormalBeats,
	assign a normal/abnormal label to each 5 sec analysis frame using a 
	majority voting strategy.
	iii) Can ignore a 5 sec segment if no annotations are available.
	iv) For each analysis frame, please compute the 




'''
def addLabel(titleString):
    plt.xlabel('Time (Sec)')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.title(titleString)



x106 = np.loadtxt("/Users/awuzaso/Documents/codingProjects/Tutorial1/MitArrhythmia/Data/106.txt")

timeSegment = 5 # sec
Fs = 360
sampleStart = 33653
L1 = Fs*5


# First 5-sec
plt.figure(1)
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,x106[sampleStart:sampleStart+L1],'r-')
addLabel("ECG Signal for Normal Heart Beat (Sample %s)"% (sampleStart))


print("Sample 35653")
coeff_01 = sp.fftpack.rfft(x106[sampleStart:sampleStart+L1],8)
print(coeff_01)
print("/////////////////////")



# Second 5-sec
sampleStart = 35468
plt.figure(2)
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)

print("Sample 35468")
coeff_01 = sp.fftpack.rfft(x106[sampleStart:sampleStart+L1],8)
print(coeff_01)
print("/////////////////////")





plt.plot(t,x106[sampleStart:sampleStart+L1],'g-')
addLabel("ECG Signal for Normal Heart Beat (Sample %s)"% (sampleStart))
# Third 5-sec
sampleStart = 37123
plt.figure(3)
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,x106[sampleStart:sampleStart+L1],'b-')
addLabel("ECG Signal for Normal Heart Beat (Sample %s)"% (sampleStart))

print("Sample 37123")
coeff_01 = sp.fftpack.rfft(x106[sampleStart:sampleStart+L1],8)
print(coeff_01)
print("/////////////////////")



# Fourth 5-sec
sampleStart = 39118
plt.figure(4)
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,x106[sampleStart:sampleStart+L1],'y-')
addLabel("ECG Signal for Normal Heart Beat (Sample %s)"% (sampleStart))

print("Sample 39118")
coeff_01 = sp.fftpack.rfft(x106[sampleStart:sampleStart+L1],8)
print(coeff_01)
print("/////////////////////")


# Fourth 5-sec
sampleStart = 40714
plt.figure(5)
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,x106[sampleStart:sampleStart+L1],'r--')
addLabel("ECG Signal for Normal Heart Beat (Sample %s)"% (sampleStart))

print("Sample 40714")
coeff_01 = sp.fftpack.rfft(x106[sampleStart:sampleStart+L1],8)
print(coeff_01)
print("/////////////////////")


plt.show()
