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

def graphGrid(grid, imgNum, graphType=0, stats=False):

    #initialise variables
    nx=grid.nX(); dx=grid.dX(); ny=grid.nY(); dy=grid.dY()
    xmax=0.5*nx*dx; xmin=-0.5*nx*dx
    ymax=0.5*ny*dy; ymin=-0.5*ny*dy
    
    nxbin=int(grid.nX())
    nybin=int(grid.nY())
    #comes from a histogram bin rule
    #(on wiki need to find better source)
    
    #for arrow plot
    if graphType == 3:
        nxbin = int(nxbin/4)
        nybin = int(nybin/4)

    fileName="graphs"
    pathName = os.path.join( ".", "root", fileName, imgNum + ".png" )
    
    gStyle.SetPalette(kBird) #make pretty (set colours)
    gStyle.SetOptStat(0) #hides information about mean x,y ect
    if stats == True:
        gStyle.SetOptStat(1)

    #define graph
    histo = TH2D("histo", "Histogram from array;x;y",
                 nxbin,xmin,xmax, #xbin,xrange
                 nybin,ymin,ymax) #ybin,yrange

    #fill graph with weights from array. The total in each bin will be the sum of the squares of the weights
    #x,y values from min to max, increment (max-min)/array size 
    for i in xrange(grid.nX()):
        for j in xrange(grid.nY()):
            histo.Fill(float(i)*(xmax-xmin)/grid.nX()+xmin,
                       float(j)*(ymax-ymin)/grid.nY()+ymin,
                       grid[i][j])
    #draw graph
    #to plot contour uncomment next 4 comments
    c = TCanvas("c", "Canvas", 850, 850)
    if graphType == 0:
        histo.Draw("Colz") #2d heatmap
        c.SetRightMargin(0.13)
    elif graphType == 1:
        histo.Draw("Cont1") #contour
    elif graphType == 2:
        histo.Draw("LEGO1") #3d boxes
    elif graphType == 3:
        histo.Draw("ARR") #arrow mode
    c.Update()

    #save graph as a png file (commented out for now)
    img = TImage.Create()
    img.FromPad(c)
    img.WriteImage(pathName)

    #set to stop on keypress
    #raw_input("Please press any key to quit")

    c.Close()
    del c
    del histo

    return 0
