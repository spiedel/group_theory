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
gROOT.LoadMacro('analytical_testing_1/script.cpp')
gROOT.LoadMacro('gridExamples/ExampleGrid.h') 
gROOT.LoadMacro('analytical_testing_1/header.h')
gROOT.LoadMacro('analytical_testing_1/grid_input.cpp')
gROOT.LoadMacro('analytical_testing_1/analytical_fill_1.cpp')
gROOT.LoadMacro('LaplaceEqnSolver.cpp')
gROOT.LoadMacro('header.h')
gROOT.LoadMacro('Gauss-Seidel.cpp')
from ROOT import Grid, plotBoundary, solve, GaussSeidel

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
solvedGrid = solve(boundaryGrid)
#solvedGauss = GaussSeidel(boundaryGrid.nX(), boundaryGrid.nY(), boundaryGrid.dX(), boundaryGrid.dY(), boundaryGrid)

#####################################################################

#plotter

#for now this will make it save the output graph under a file decribing current date and time. We can eventually make a file name part of the input if necessary
outputFileName = time.strftime("%Y%m%d-%H%M%S")

graphGrid(solvedGrid, "test2", 0)
#graphGrid(solvedGauss, "something")

####################################################################
#analysis
analytical = plotBoundary(1)
graphGrid(analytical, "test3")
differenceGrid = Grid(solvedGrid.nX(), solvedGrid.nY(), solvedGrid.dX(), solvedGrid.dY())

for i in xrange(solvedGrid.nX()):
    for j in xrange(solvedGrid.nY()):
        if not np.isnan(analytical[i][j]):
            differenceGrid[i][j] = analytical[i][j]-solvedGrid[i][j]
            if differenceGrid[i][j]<0:
                differenceGrid[i][j] = -1. * differenceGrid[i][j]

graphGrid(differenceGrid, "test3", 2)