def sinusoid(Fs,F0,T):
    t=np.linspace(0,T,T*Fs)
    return (t,np.sin(2*np.pi*F0*t))

def lowpass_filter(x, lowcut, Fs, filter_order):
    nyquist_freq = 0.5 * Fs
    low = lowcut / nyquist_freq
    b, a = signal.butter(filter_order,low, btype="lowpass")
    y = signal.lfilter(b, a, x)
    return (y,b,a)

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

