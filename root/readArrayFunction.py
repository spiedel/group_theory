#Program to read in an array from a file and output it as a hitstogram
#generalised to any array size
#needs ROOT to run

#import root functions and numpy
from ROOT import gROOT, TCanvas, kBird, TH2D, gStyle, TImage
import numpy as np
import os



#load grid header file
gROOT.LoadMacro('ExampleGrid.h+')
from ROOT import Grid

def graphGrid(xmax, xmin, dx, ymax, ymin, dy, grid, imgNum) :

    #initialise variable
    nxbin=int(np.sqrt(grid.nX()))
    nybin=int(np.sqrt(grid.nY()))
    print "nxbin = %d" %nxbin
    #comes from a histogram bin rule
    #(on wiki need to find better source)
    
    fileName="graphs"
    pathName = os.path.join( ".", fileName, imgNum + ".png" )
    
    gStyle.SetPalette(kBird) #make pretty (set colours)
    gStyle.SetOptStat(0) #hides information about mean x,y ect

    #define graph
    histo = TH2D("histo", "Histogram from array;x;y",
                 nxbin,xmin,xmax, #xbin,xrange
                 nybin,ymin,ymax) #ybin,yrange

    print "Initialied graph %s" %imgNum

    #fill graph with weights from array. The total in each bin will be the sum of the squares of the weights
    #x,y values from min to max, increment (max-min)/array size 
    for i in xrange(grid.nX()):
        for j in xrange(grid.nY()):
            histo.Fill(float(i)*(xmax-xmin)/grid.nX()+xmin,
                       float(j)*(ymax-ymin)/grid.nY()+ymin,
                       grid[i][j])
    print "Filed Graph %s successfully" % imgNum
    #draw graph
    #to plot contour uncomment next 4 comments
    c = TCanvas("c", "Canvas", 800, 800)
    #c.Divide(2,1)
    #c.cd(1)
    histo.Draw("Colz") #2d heatmap
    #c.cd(2)
    #histo.Draw("Cont1") #3d histogram
    c.Update()

    #save graph as a png file (commented out for now)
    img = TImage.Create()
    img.FromPad(c)
    img.WriteImage(pathName)

    #set to stop on keypress
    raw_input("Please press any key to quit")

    c.Close()
    del c
    del histo

    return 0

#initialise graph axes
g_dx=0.2
g_dy=0.1

#define array as a grid
array = Grid(500,500,g_dx,g_dy)

print "Initialised empty Grid"
#fill array with random numbers
for i in xrange(array.nX()):
    for j in xrange(array.nY()):
        array[i][j]=float(20*np.random.random_sample()-10)
        
print "Filled Grid sucessfully"

#example call
#this shoulb be importable as a function and can be run from another file with any grid. x and y values are determined by boundary conditions
graphGrid(xmax=20, xmin=10, dx=array.dX(), #x variables
          ymax=5, ymin=0, dy=array.dY(), #y variables
          grid=array, imgNum="1") #grid and save file
graphGrid(xmax=30, xmin=0, dx=array.dX(),
          ymax=16, ymin=-10, dy=array.dY(),
          grid=array, imgNum="2")

del array
