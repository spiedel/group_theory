from ROOT import gROOT, gSystem

#load header file
gROOT.LoadMacro("ExampleGrid.h")

#import the grid class
from ROOT import Grid

#define a new grid
mygrid = Grid(5,10,0.1,0.2)

#evaluate points
mygrid[2][1]=4
mygrid[7][4]=2

#probably the wrong way round in x and y, but prints grid
for i in xrange(10):
    for j in xrange(5):
        print "%d " % mygrid[i][j],
    print

del mygrid
