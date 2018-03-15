#A program for top level structure

#adding any directories with python files to include to the path
#need to look into __init__ files
import sys, os, inspect
cmd_subfolder = os.path.realpath(os.path.abspath(os.path.split(inspect.getfile( inspect.currentframe() ))[0]) + "/root")
cmd_subfolder_1 = os.path.realpath(os.path.abspath(os.path.split(inspect.getfile( inspect.currentframe() ))[0]) + "/program")
if cmd_subfolder not in sys.path:
    sys.path.insert(0, cmd_subfolder)
    sys.path.insert(0, cmd_subfolder_1)

#load macros of C++ files
from ROOT import gROOT
#format gROOT.LoadMacro("path_from_current_file")
gROOT.LoadMacro('gridExamples/ExampleGrid.h') 
gROOT.LoadMacro('program/grid_input.cpp')
gROOT.LoadMacro('program/analytical_fill_1.cpp')
gROOT.LoadMacro('program/analytical_fill_2.cpp')
gROOT.LoadMacro('numerical/GaussSeidel.cpp')
gROOT.LoadMacro('numerical/jacobi.cpp')
gROOT.LoadMacro('numerical/SOR.cpp')
from ROOT import Grid, grid_input, jacobi, gauss_seidel, analytical_fill_1, analytical_fill_2, SOR

#when it imports the function is runs it from the folder you are in
#so need to take that into account when writing code to save to a file
from graphModule import graphGrid
#import GUI

import time
import numpy as np

#################################################################################################
#function to find difference between the analytical and the numberical solutions
def find_diff_from_analytical(analytical, solvedGrid):
    graphGrid(analytical, "Analytical", 0)
    differenceGrid = Grid(solvedGrid.nX(), solvedGrid.nY(), solvedGrid.dX(), solvedGrid.dY())
    total = 0
    count = 0

    for i in xrange(solvedGrid.nX()):
        for j in xrange(solvedGrid.nY()):
            #check you aren't using a nan value
            if not np.isnan(analytical[i][j]):
                differenceGrid[i][j] = (analytical[i][j]-solvedGrid[i][j])

                #get absolute value of the error
                if differenceGrid[i][j]<0:
                    differenceGrid[i][j] = -1. * differenceGrid[i][j]

                total = total + differenceGrid[i][j]
                count+= 1

    graphGrid(differenceGrid, "test4", 0, False)

    average = float(total / count)

    print "The average error is %.3f" % average
    del differenceGrid, analytical

    return


#####################################################################


#input and parser
#grid_input takes a conditions file as an argument
#for output from the GUI use "conditions.txt" (the default value with no argument given)
#if you want to test against an analytical use conditions1.txt or conditions2.txt
boundaryGrid = grid_input('program/conditions1.txt')
print "Filled in boundary conditions"
#####################################################################

#solver
#structure is
#solvedGrid = method(boundaryGrid, n_max, tolerance)
#solvedGrid = jacobi(boundaryGrid, 5000, 0.00001)
#solvedGrid = gauss_seidel(boundaryGrid, 5000, 0.00001)
solvedGrid = SOR(boundaryGrid, 5000, 0.00001, 1.9) 
#last factor is relaxtion constant, optional - default value is 1.9
#####################################################################

#plotter

#for now this will make it save the output graph under a file decribing current date and time. 
#We can eventually make a file name part of the input if necessary
outputFileName = time.strftime("%Y%m%d-%H%M%S")
graphGrid(solvedGrid, outputFileName,0)

####################################################################
#analysis
#analytical_fill_1 covers problem 0, analytical_fill_2 covers problem one.
#If you want to use analytical use conditions1.txt or conditions2.txt
ifAnalyse = raw_input("Do you want to compare to an analytical soltion? Enter y to continue ")
if ifAnalyse == "y" or ifAnalyse == "Y":

    whichAnalytical = raw_input("Compare to problem 0 or 1? ")
    if whichAnalytical == "0":
        analytical = analytical_fill_1(boundaryGrid.nX(), boundaryGrid.nY(), boundaryGrid.dX(), boundaryGrid.dY(), boundaryGrid)
        find_diff_from_analytical(analytical, solvedGrid)
    elif whichAnalytical == "1":
        analytical = analytical_fill_2(boundaryGrid.nX(), boundaryGrid.nY(), boundaryGrid.dX(), boundaryGrid.dY(), boundaryGrid)
        find_diff_from_analytical(analytical, solvedGrid)
    else: 
        print "Not a valid analytical result"
else:
    print "Not comparing to analytical"

del solvedGrid, boundaryGrid

