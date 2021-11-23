import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

def addLabel(titleString):
    plt.xlabel('Time (Sec)')
    plt.ylabel('Skin Conductance')
    plt.grid(True)
    plt.title(titleString)

'''
b) Visualization of EDA signals:

    i) Plot EDA signals from different participants and mark exampels of skin conductance responses (SCR).
    ii) What do you observe?
    iii) Is there variability in the data?
'''

EDA_signal_01_T1 = np.loadtxt("/Users/awuzaso/Documents/codingProjects/Tutorial1/DEAP/Data/s01_Trial1")

EDA_signal_02_T1 = np.loadtxt("/Users/awuzaso/Documents/codingProjects/Tutorial1/DEAP/Data/s02_Trial1")

EDA_signal_03_T1 = np.loadtxt("/Users/awuzaso/Documents/codingProjects/Tutorial1/DEAP/Data/s03_Trial1")

EDA_signal_04_T1 = np.loadtxt("/Users/awuzaso/Documents/codingProjects/Tutorial1/DEAP/Data/s04_Trial1")

EDA_signal_05_T1 = np.loadtxt("/Users/awuzaso/Documents/codingProjects/Tutorial1/DEAP/Data/s05_Trial1")

EDA_signal_06_T1 = np.loadtxt("/Users/awuzaso/Documents/codingProjects/Tutorial1/DEAP/Data/s06_Trial1")

# Setup:
Fs = 1500
L=20
sampleStart = 83
L1 = 360*20
timeSpan = Fs*1


plt.figure("2_2_b_s01_Trial_1")
t=np.linspace(0,timeSpan,timeSpan)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,EDA_signal_01_T1[0:timeSpan],'r-')
addLabel("EDA Reactivity to Multimedia Content Original (Fs %s)"% (Fs))


plt.figure("2_2_b_s01_Trial_2")
t=np.linspace(0,timeSpan,timeSpan)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,EDA_signal_02_T1[0:timeSpan],'g-')
addLabel("EDA Reactivity to Multimedia Content Original (Fs %s)"% (Fs))


plt.figure("2_2_b_s01_Trial_3")
t=np.linspace(0,timeSpan,timeSpan)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,EDA_signal_03_T1[0:timeSpan],'b-')
addLabel("EDA Reactivity to Multimedia Content Original (Fs %s)"% (Fs))

plt.figure("2_2_b_s01_Trial_4")
t=np.linspace(0,timeSpan,timeSpan)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,EDA_signal_04_T1[0:timeSpan],'r-')
addLabel("EDA Reactivity to Multimedia Content Original (Fs %s)"% (Fs))

plt.figure("2_2_b_s01_Trial_5")
t=np.linspace(0,timeSpan,timeSpan)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,EDA_signal_05_T1[0:timeSpan],'g-')
addLabel("EDA Reactivity to Multimedia Content Original (Fs %s)"% (Fs))

plt.figure("2_2_b_s01_Trial_6")
t=np.linspace(0,timeSpan,timeSpan)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,EDA_signal_06_T1[0:timeSpan],'b-')
addLabel("EDA Reactivity to Multimedia Content Original (Fs %s)"% (Fs))

plt.show()