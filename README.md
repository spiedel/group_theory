# group_theory 
Numerical Solution to Laplace Equation

Prerequisites:
Python2
ROOT (available from https://root.cern.ch/)
PyROOT (accessed through the root build if you compile it yourself, python2root using yum or libroot-bindings-python using apt-get)

Basic running:
To run the whole program, use the file "./test.sh". This will need to be made excecutable first. 

Structure:
This program is split in three parts: a program folder that contains all of the files needed for the input and GUI; a numerical folder that contains all three numerical methods; and a root folder that contains all the files needed for plotting. The second two are pulled together in structure.py, and the GUI is accessed through calling "python program/gui.py" or "./test.sh". 
Currently it is set up to use the SOR method. To use a different method uncomment the relevant lines in the structure.py file. For Jacobi you want the numerical_solution function and for Gauss-Seidel you want the gauss_seidel function.

Input file:
"conditions.txt" contains the current boundary conditions. This is overwritten everytime the GUI is run. To run the same conditions twice simply call "python structure.py". This will take the current conditions file and run it

The first line has the structure:
xrange, dx, yrange, dy
Where xrange and yrange give the value of half the graph - for example the x axis will go from -xrange to +xrange
dx and dy give the mesh size of the graph

The next lines code in different shapes as follows:

For a circle;
[1,r,x_0,y_0,V]

r=radius
(x_0,y_0)=centre of circle
V=potential on circle

For a line;
[2,x_0,y_0,x_n,y_n,V]

(x_0,y_0)=starting coordinate
(x_n,y_n)=end coordinate
V=potential on line

For a rectangle;
[3,x_0,y_0,dx,dy,V]

(x_0,y_0)=left-hend upper corner
dx=x-sidelenght
dy=y-sidelenght
V=potential on rectangle
