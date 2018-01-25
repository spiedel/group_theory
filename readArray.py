#Program to read in an array from a file and output it as a hitstogram
#needs ROOT to run
#currently only works with 100*100 arrays with x and y values from -10 to +10


#import root functions and numpy
from ROOT import TCanvas, kBird, TH2F, gStyle
import numpy as np

#make pretty
gStyle.SetPalette(kBird)

#define array from file
#array=np.zeros((100,100))
array = np.loadtxt("example.txt")
    
#define graph
histo = TH2F("histo", "Histogram from array;1;2",
             100,-10,10, #x range
             100,-10,10) #y range


#fill graph with values from array
for i in range(0,100):
    for j in range(0,100):
        histo.Fill((i-50)/5.,(j-50)/5.,array[i][j])

#draw graph
c = TCanvas("c", "Canvas", 800, 800)
c.Divide(2,1)
c.cd(1)
histo.Draw("Colz")
c.cd(2)
histo.Draw("lego2")
c.Update()

#set to stop on keypress
raw_input("Please press any key to quit")

