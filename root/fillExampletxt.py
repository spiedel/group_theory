import numpy as np
import pickle

#open file
myfile = open("example.txt", "w")

#does work for larger values but takes a long time to plot
xsize=150
ysize=200

#initialise array of random numbers
array = 20*np.random.rand(xsize,ysize)-10

#talk to others about using pickle?
#for i in range(0,100):
#    pickle.dump(array[i], myfile)

#fill human readable file
for i in range(0,xsize):
    for j in range (0,ysize):
        myfile.write('{} '.format(array[i][j]))
    myfile.write('\n')
        
    
myfile.close()
