#module to read in an array from a file and output it as a hitstogram
#generalised to any array size
#needs ROOT to run

# #import root functions and numpy
from ROOT import gROOT, TCanvas, kBird, TH2D, gStyle, TImage
# import numpy as np
import os



#load grid header file
#gROOT.LoadMacro('gridExamples/ExampleGrid.h')
#from ROOT import Grid

def graphGrid(grid, imgNum) :

    #initialise variables
    nx=grid.nX(); dx=grid.dX(); ny=grid.nY(); dy=grid.dY()
    xmax=0.5*nx*dx; xmin=-0.5*nx*dx
    ymax=0.5*ny*dy; ymin=-0.5*ny*dy
    
    nxbin=int(grid.nX()-1)
    nybin=int(grid.nY()-1)
    print "nxbin = %d" %nxbin
    #comes from a histogram bin rule
    #(on wiki need to find better source)
    
    fileName="graphs"
    pathName = os.path.join( ".", "root", fileName, imgNum + ".png" )
    
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
