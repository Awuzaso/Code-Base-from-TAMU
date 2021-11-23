import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

image_i = [[64, 188, 164, 161, 195], 
		   [178, 201, 197, 150, 137],
		   [174, 168, 181, 190, 184],
		   [131, 179, 176, 185, 198],
		   [92, 185, 179, 133, 167]]

image_i_f1 = image_i

filter_f1 =  [[1, 1, 1],
			 [1, 1, 1],
			 [1, 1, 1]]

filter_f2 =  [[-1, -2, -1],
			 [0, 0, 0],
			 [1, 2, 1]]

filter_f3 =  [[-1, -1, -1],
			 [-1, 9, -1],
			 [-1, -1, -1]]




import matplotlib.pyplot as plt
import matplotlib.image as mpimg

#plt.imshow(image_i)
#plt.show()


#find center position of kernel (half of kernel size)

kCol = 3
kRow = 3
kCenterX =kCol / 2
kCenterY = kRow / 2
row = 5
column = 5

print(kCenterX)
print(kCenterY)



for i in range(row):
	for j in range(column):
		m = 0
		while (m < kRow):
			mm = kRow - 1 - m
			n = 0
			m = m+1
			while (n < kCol):
				nn = kCol - 1 - n
				
				ii = i + (kCenterY - mm)
				jj = j + (kCenterX - nn)
				n = n+1
				if( ii >= 0 and ii < row and jj >= 0 and jj < column ): 
					image_i_f1[i][j] += image_i[ii][jj] * filter_f3[mm][nn]
 					print("Done.")

plt.imshow(image_i_f1)
plt.show()