#A program for top level structure

#adding any directories with python files to include to the path
#need to look into __init__ files
import sys
sys.path.insert(0, "./root/")

#load macros of C++ files
from ROOT import gROOT
#format gROOT.LoadMacro("path_from_current_file")
gROOT.LoadMacro('gridExamples/ExampleGrid.h') 
from ROOT import Grid

#when it imports the function is runs it from the folder you are in
#so need to take that into account when writing code to save to a file
from graphModule import graphGrid 

import time
import numpy as np
import os

#####################################################################

#input and parser
#boundaryGrid = someInputFunction()

#####################################################################

#solver
#solvedGrid = someSolverFunction(boundaryGrid)

#####################################################################

#plotter

#for now this will make it save the output graph under a file decribing current date and time. We can eventually make a file name part of the input if necessary
outputFileName = time.strftime("%Y%m%d-%H%M%S")

#example grid for testing purposes
solvedGrid = Grid(100,100,0.2,0.1)
print "Initialised empty Grid"
#fill array with random numbers
for i in xrange(solvedGrid.nX()):
    for j in xrange(solvedGrid.nY()):
        solvedGrid[i][j]=float(20*np.random.random_sample()-10)
print "Filled Grid sucessfully"

graphGrid(solvedGrid, outputFileName)
