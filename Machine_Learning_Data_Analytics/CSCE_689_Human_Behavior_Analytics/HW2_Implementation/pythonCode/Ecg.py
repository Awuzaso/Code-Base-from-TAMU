import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

x123 = np.loadtxt("./123.txt")
x123=x123[:,2]
x208 = np.loadtxt("./208.txt")
x208=x208[:,2]

L=1000
Fs=360
plt.figure(1)
t=np.linspace(1,L,L)/Fs
plt.plot(t,x123[0:L],'b-')
plt.show()
#mpld3.display(fig)