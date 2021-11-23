import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

def addLabel(titleString):
    plt.xlabel('Time (Sec)')
    plt.ylabel('Skin Conductance')
    plt.grid(True)
    plt.title(titleString)

def findpeaks(data, spacing, limit):
        print(len(data),spacing)
        x = np.zeros(len(data) + 2 * spacing)
        x[:spacing] = data[0] - 1.e-6
        x[-spacing:] = data[-1] - 1.e-6
        x[spacing:spacing + len(data)] = data
        peak_candidate = np.zeros(len(data))
        peak_candidate[:] = True
        for s in range(spacing):
            start = spacing - s - 1
            h_b = x[start: start + len(data)]  # before
            start = spacing
            h_c = x[start: start + len(data)]  # central
            start = spacing + s + 1
            h_a = x[start: start + len(data)]  # after
            peak_candidate = np.logical_and(peak_candidate, np.logical_and(h_c > h_b, h_c > h_a))
        ind = np.argwhere(peak_candidate)
        ind = ind.reshape(ind.size)
        if limit is not None:
            ind = ind[data[ind] > limit]
        return ind

'''
c) Feature extraction for each signal. Provide several examples of EDA signals and resulting features.:
    i) Extract the mean level (also called skin condutance level, SCL).
    ii) SCR frequency
    iii) mean SCR amplitude (i.e., the average amplitude of all SCRs)
    


'''



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


meanSCL = np.empty(6)

plt.figure("2_2_b_s01_Trial_1")
t=np.linspace(0,timeSpan,timeSpan)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,EDA_signal_01_T1[0:timeSpan],'r-')

meanSCL[0] = np.mean(EDA_signal_01_T1[0:timeSpan])
meanSCL[1] = np.mean(EDA_signal_02_T1[0:timeSpan])
meanSCL[2] = np.mean(EDA_signal_03_T1[0:timeSpan])
meanSCL[3] = np.mean(EDA_signal_04_T1[0:timeSpan])
meanSCL[4] = np.mean(EDA_signal_05_T1[0:timeSpan])
meanSCL[5] = np.mean(EDA_signal_06_T1[0:timeSpan])

(findpeaks_limit,findpeaks_spacing)=(0.35,50)
peaks_indicesEDA_signal_01_T1 = findpeaks(EDA_signal_01_T1,findpeaks_spacing,findpeaks_limit)
peaks_indicesEDA_signal_02_T1 = findpeaks(EDA_signal_02_T1,findpeaks_spacing,findpeaks_limit)
peaks_indicesEDA_signal_03_T1 = findpeaks(EDA_signal_03_T1,findpeaks_spacing,findpeaks_limit)
peaks_indicesEDA_signal_04_T1 = findpeaks(EDA_signal_04_T1,findpeaks_spacing,findpeaks_limit)
peaks_indicesEDA_signal_05_T1 = findpeaks(EDA_signal_05_T1,findpeaks_spacing,findpeaks_limit)
peaks_indicesEDA_signal_06_T1 = findpeaks(EDA_signal_06_T1,findpeaks_spacing,findpeaks_limit)

SCR_freq_01 = len(peaks_indicesEDA_signal_01_T1)/timeSpan
print(SCR_freq_01)


print(meanSCL)

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