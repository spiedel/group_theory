#Program to read in an array from a file and output it as a hitstogram
#generalised to any array size
#needs ROOT to run


#import root functions and numpy
from ROOT import TCanvas, kBird, TH2F, gStyle
import numpy as np

#initialise graph axes - this should eventually come from input file
xmax=10
xmin=-10
ymax=10
ymin=-10

#make pretty (set colours)
gStyle.SetPalette(kBird)

#define array from file
array = np.loadtxt("example.txt")
#from here array.shape is used to get dimensions of input array
#if dimensions are large takes a very long time to run - look into hist2image

#define graph
histo = TH2F("histo", "Histogram from array;x;y",
             array.shape[0],xmin,xmax, #x range
             array.shape[1],ymin,ymax) #y range


#fill graph with values from array.
#x,y values from min to max, increment (max-min)/array size 
for i in range(0,array.shape[0]):
    for j in range(0,array.shape[1]):
        histo.Fill(float(i)*(xmax-xmin)/array.shape[0]+xmin,
                   float(j)*(ymax-ymin)/array.shape[1]+ymin,
                   array[i][j])

#draw graph
#to plot 3d histogram uncomment next 4 comments, but slows down program
c = TCanvas("c", "Canvas", 800, 800)
#c.Divide(2,1)
#c.cd(1)
histo.Draw("Colz") #2d heatmap
#c.cd(2)
#histo.Draw("lego2") #3d histogram
c.Update()

#set to stop on keypress
raw_input("Please press any key to quit")
