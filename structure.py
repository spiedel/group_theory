#A program for top level structure

#adding any directories with python files to include to the path
#need to look into __init__ files
import sys, os, inspect
cmd_subfolder = os.path.realpath(os.path.abspath(os.path.split(inspect.getfile( inspect.currentframe() ))[0]) + "/root")
if cmd_subfolder not in sys.path:
    sys.path.insert(0, cmd_subfolder)

#load macros of C++ files
from ROOT import gROOT
#format gROOT.LoadMacro("path_from_current_file")
gROOT.LoadMacro('gridExamples/ExampleGrid.h')
gROOT.LoadMacro('program/script.cpp') 
#gROOT.LoadMacro('program/header.h')
gROOT.LoadMacro('program/grid_input.cpp')
gROOT.LoadMacro('program/analytical_fill_1.cpp')
gROOT.LoadMacro('program/analytical_fill_2.cpp')
#gROOT.LoadMacro('LaplaceEqnSolver.cpp')
gROOT.LoadMacro('numerical/numerical_solution.cpp')
from ROOT import Grid, plotBoundary, numerical_solution

#when it imports the function is runs it from the folder you are in
#so need to take that into account when writing code to save to a file
from graphModule import graphGrid

import time
import numpy as np

#####################################################################

#input and parser
boundaryGrid = plotBoundary()
graphGrid(boundaryGrid, "test")

#####################################################################

#solver
#solvedGrid = solve(boundaryGrid)
#solvedGauss = GaussSeidel(boundaryGrid.nX(), boundaryGrid.nY(), boundaryGrid.dX(), boundaryGrid.dY(), boundaryGrid)
solvedSofie = numerical_solution(boundaryGrid.nX(), boundaryGrid.nY(), boundaryGrid.dX(), boundaryGrid.dY(), boundaryGrid)

#####################################################################

#plotter

#for now this will make it save the output graph under a file decribing current date and time. We can eventually make a file name part of the input if necessary
outputFileName = time.strftime("%Y%m%d-%H%M%S")

#graphGrid(solvedGrid, "test1")
graphGrid(solvedSofie, "test2",0)
#graphGrid(solvedGauss, "something")

####################################################################
#analysis
analytical = plotBoundary(1)
graphGrid(analytical, "test3", 0)
differenceGrid = Grid(solvedSofie.nX(), solvedSofie.nY(), solvedSofie.dX(), solvedSofie.dY())
total = 0

for i in xrange(solvedSofie.nX()):
    for j in xrange(solvedSofie.nY()):
        #check you aren't using a nan value
        if not np.isnan(analytical[i][j]):
            differenceGrid[i][j] = (analytical[i][j]-solvedSofie[i][j])

            #get absolute value of the error
            if differenceGrid[i][j]<0:
                differenceGrid[i][j] = -1. * differenceGrid[i][j]

            total = total + differenceGrid[i][j]

graphGrid(differenceGrid, "test4", 0, False)

average = float(total / (i*j))

print "The average error is %.3f" % average

del solvedSofie, boundaryGrid, differenceGrid
