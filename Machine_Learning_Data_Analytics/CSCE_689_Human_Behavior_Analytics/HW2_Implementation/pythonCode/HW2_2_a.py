import numpy as np
import matplotlib.pyplot as plt
from scipy import signal
import sys


def addLabel(titleString):
    plt.xlabel('Time (Sec)')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.title(titleString)

def lowpass_filter(x, lowcut, Fs, filter_order):
    nyquist_freq = 0.5 * Fs
    low = lowcut / nyquist_freq
    b, a = signal.butter(filter_order,low, btype="lowpass")
    y = signal.lfilter(b, a, x)
    return (y,b,a)

'''
a) EDA signal denoising: Use a low-pass filter to filter out unwanted high-requency 
noise resulting from electrical interference.

    i) Experiment with different cutoff frequencies at ??Hz.

    ii) Plot the original and smoothed EDA signals.

    iii) What do you observe?
'''

EDA_signal = np.loadtxt("/Users/awuzaso/Documents/codingProjects/Tutorial1/DEAP/Data/s01_Trial18")




Fs = int(sys.argv[1])
L=20


sampleStart = 83
L1 = 360*10


plt.figure("2_2_a_%s_original"% (Fs))
t=np.linspace(0,Fs,Fs)/Fs # np.linspace(start, stop, num = 50, ...)
plt.plot(t,EDA_signal[0:Fs],'b-') 
addLabel("EDA Reactivity to Multimedia Content Original (Fs %s)"% (Fs))


# Smoothing
lowcutVal = 15

(Denoise_EDA_Signal,b,a) = lowpass_filter(EDA_signal,lowcutVal,Fs,1)

plt.figure("2_2_a_%s_smooth"% (Fs))
t=np.linspace(0,Fs,Fs)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,Denoise_EDA_Signal[0:Fs],'b-')
addLabel("EDA Reactivity to Multimedia Content Smooth (Fs %s)"% (Fs))


plt.show()
