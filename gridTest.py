from ROOT import gSystem, gROOT

#load header file
gROOT.LoadMacro("ExampleGrid.h")

#import the grid class
from ROOT import Grid

#define a new grid
mygrid = Grid(10,15,0.1,0.2)

#evaluate one point
mygrid[6][4]=4

#probably the wrong way round in x and y, but prints grid
for i in xrange(10):
    for j in xrange(15):
        print "%d " % mygrid[i][j],
    print

