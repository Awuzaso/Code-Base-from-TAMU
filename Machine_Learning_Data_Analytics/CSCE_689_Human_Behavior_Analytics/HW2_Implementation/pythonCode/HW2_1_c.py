# Import necessary libraries.
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

# Pan-Tomkins QRS Detection: 

#Instructions:
'''
a) Implement the Pan-Tomkins algorithm to detect the QRS complexes of all
signals:
    i) bandpass filtering
    ii) differentiation
    iii) squaring
    iv) moving average filtering
    v) peak detection
    
b) Using the annotation files in folder Annotations_QRSLocation, please provide 
the following measures between detected and actual QRS complexes using a 
forgiving threshold of 0.5 sec:
    i) precision
    ii) recall

c) Visualize your results for different ECG segments containing normal and premature ventricular beats.
'''


# c) QRS detection:
'''
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
'''
def bandpass_filter(x, lowcut, highcut, Fs, filter_order):
    nyquist_freq = 0.5 * Fs
    low = lowcut / nyquist_freq
    high = highcut / nyquist_freq
    b, a = signal.butter(filter_order, [low, high], btype="band")
    y = signal.lfilter(b, a, x)
    return (y,b,a)

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

# band-pass filter
def bandPassFilter(in_x,in_lowcut,in_highcut,in_filter_order):
    x = in_x
    (lowcut,highcut,filter_order)=(in_lowcut,in_highcut,in_filter_order)
    (x_bfilt,b,a)=bandpass_filter(x, lowcut, highcut, Fs, filter_order)
    print(L,len(t),len(x))
    plt.figure(1);plt.plot(np.linspace(1,len(x_bfilt),len(x_bfilt))/Fs,x,'b-',t,x_bfilt,'g--')
    return (x_bfilt,b,a)

'''
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
'''
def addLabel(titleString):
    plt.xlabel('Time (Sec)')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.title(titleString)


x106 = np.loadtxt("/Users/awuzaso/Documents/codingProjects/Tutorial1/MitArrhythmia/Data/106.txt")

Fs = 360

L1 = 360*10

# Bandpass Filter


sampleStart = 33820
#sampleStart = 32867
L1 = 360*7
x = x106[sampleStart:sampleStart+L1]

plt.figure(1)
t=np.linspace(sampleStart,sampleStart+L1,L1)/Fs# np.linspace(start, stop, num = 50, ...)
plt.plot(t,x106[sampleStart:sampleStart+L1],'b-')
addLabel("ECG Signal for Normal Heart Beat (Sample %s)"% (sampleStart))

'''
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Band Pass Filter
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
'''
(lowcut,highcut,filter_order)=(4,15,1)
(x_bfilt,b,a)=bandpass_filter(x, lowcut, highcut, Fs, filter_order)
plt.figure("Bandpass Filter")
#plt.plot(np.linspace(1,len(x_bfilt),len(x_bfilt))/Fs,x,'b-',t,x_bfilt,'g--')
plt.plot(np.linspace(sampleStart,sampleStart+len(x_bfilt),len(x_bfilt))/Fs,x,'b-',t,x_bfilt,'g--')

addLabel("ECG Signal for Normal Heart Beat (Sample %s)"% (sampleStart))



'''
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Differentiation
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
'''
x_bfilt_diff=np.ediff1d(x_bfilt)
plt.figure("Differentiation")
#plt.plot(np.linspace(1,len(x_bfilt_diff),len(x_bfilt_diff))/Fs,x_bfilt_diff,'r-')
plt.plot(np.linspace(sampleStart,sampleStart+len(x_bfilt_diff),len(x_bfilt_diff))/Fs,x_bfilt_diff,'r-')
addLabel("ECG Signal for Normal Heart Beat (Sample %s)"% (sampleStart))




'''
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Squaring
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
'''
# square
x_bfilt_diff_sq=x_bfilt_diff**2
plt.figure("Square")
#plt.plot(np.linspace(1,len(x_bfilt_diff_sq),len(x_bfilt_diff_sq))/Fs,x_bfilt_diff_sq,'k--')
plt.plot(np.linspace(sampleStart,sampleStart+len(x_bfilt_diff_sq),len(x_bfilt_diff_sq))/Fs,x_bfilt_diff_sq,'k--')
addLabel("ECG Signal for Normal Heart Beat (Sample %s)"% (sampleStart))




'''
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Moving Average Filter
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
'''
# moving average filter
MAfilter_len=15
x_bfilt_diff_sq_smooth = np.convolve(x_bfilt_diff_sq, np.ones(MAfilter_len))
plt.figure("Moving Average Filter")
#plt.plot(np.linspace(1,len(x_bfilt_diff_sq_smooth),len(x_bfilt_diff_sq_smooth))/Fs,x_bfilt_diff_sq_smooth,'k-')
plt.plot(np.linspace(sampleStart,sampleStart+len(x_bfilt_diff_sq_smooth),len(x_bfilt_diff_sq_smooth))/Fs,x_bfilt_diff_sq_smooth,'k-')
addLabel("ECG Signal for Normal Heart Beat (Sample %s)"% (sampleStart))




'''
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Peak detection
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
'''
(findpeaks_limit,findpeaks_spacing)=(0.9,50)
peaks_indices = findpeaks(x_bfilt_diff_sq_smooth,findpeaks_spacing,findpeaks_limit) 
#(peaks_indices/Fs)
plt.figure("Peak detection");
lin = np.linspace(1,len(x),len(x))/Fs

#plt.plot(np.linspace(sampleStart,sampleStart+len(x_bfilt_diff_sq_smooth),len(x_bfilt_diff_sq_smooth))/Fs,x_bfilt_diff_sq_smooth,'k-',peaks_indices/Fs,x[peaks_indices],'ro')

#plt.plot(np.linspace(1,len(x),len(x))/Fs,x,'b-',peaks_indices/Fs,x[peaks_indices], 'ro')



plt.plot(np.linspace(1,len(x),len(x))/Fs,x,'b-',peaks_indices/Fs,x[peaks_indices], 'ro')

#plt.plot(np.linspace(sampleStart,sampleStart+len(x),len(x))/Fs,x,'b-',(peaks_indices/Fs)+1427,x[peaks_indices]+1427, 'ro')

#plt.plot(t,x106[sampleStart:sampleStart+L1],'b-',(peaks_indices/Fs),x[peaks_indices], 'ro')


#plt.plot(np.linspace(sampleStart,sampleStart+len(x),len(x))/Fs,x,'b-',peaks_indices/Fs,x[peaks_indices], 'ro')


addLabel("ECG Signal for Normal Heart Beat (Sample %s)"% (sampleStart))

print(x)
print((peaks_indices/Fs)+1427)

plt.show()

