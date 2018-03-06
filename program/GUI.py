from Tkinter import *

# ------- Functions --------
# -- Done Button 1
# this is for after getting x and y range
def doneGrid(*arg):
    global mess, grid_x, grid_y, grid_dx, grid_dy # for future use when inputint values on for example lines.
    global grid1
    
    if (len(arg[1].get()) != 0 and len(arg[2].get()) != 0 and len(arg[3].get()) != 0 and len(arg[4].get()) !=0 ):
        # getting values from entries
        grid_x = float(arg[1].get())
        grid_dx = float(arg[2].get())
        grid_y = float(arg[3].get())
        grid_dy = float(arg[4].get())
        
        file_obj.write(arg[1].get() + " " + arg[2].get() + " " + arg[3].get() + " " + arg[4].get() + "\n")

        # Remove everything by destroying it
        for a in range(1,len(arg)):
            arg[a].destroy()
        
        # Running next step
        shape_inputs(arg[0])
    else:
        # message about filling entries
        mess = Label(master, text="All entries need values.")
        mess.grid(row=9,columnspan=6)

def doneGeo(index,grid1):
    global mess, done

    if index == 1: # Circle
        if (len(ent_r.get()) != 0 and len(ent_x0.get()) != 0 and len(ent_y0.get()) != 0 and len(ent_pot.get()) != 0):
            # getting values from entries
            x_0 = ent_x0.get()
            y_0 = ent_y0.get()
            r = ent_r.get()
            file_obj.write("1 " + r + " " + x_0 + " " + y_0 + " " + ent_pot.get() + "\n")

            # detroy the widgets
            ent_r.destroy(),ent_x0.destroy(),ent_y0.destroy(),ent_pot.destroy()
            c_r.destroy(), centre.destroy(), pot.destroy(), done.destroy(), exit_btn.destroy(), mess.destroy()

            # runing the GUI again
            shape_inputs(grid1)
            # draw on canvas
            drawing(1,grid1,float(x_0),float(y_0),float(r))
        else:
            # message about filling entries
            mess = Label(master, text= "All entries need values.")
            mess.grid(row=6, column=5,columnspan=2)
        
    elif index == 2: # Line
        if (len(ent_x0.get()) != 0 and len(ent_y0.get()) != 0 and len(ent_xn.get()) != 0 and len(ent_yn.get()) != 0 and len(ent_pot.get()) != 0):
            # getting values from the entries and checking for inf
            # x_0 = +- inf
            if (ent_x0.get() == "inf"):
                x_0 = grid_x
            elif (ent_x0.get() == "-inf"):
                x_0 = 0-grid_x
            else:
                x_0 = ent_x0.get()
            # y_0 = +- inf
            if (ent_y0.get() == "inf"):
                y_0 = grid_y
            elif (ent_y0.get() == "-inf"):
                y_0 = 0-grid_y
            else:
                y_0 = ent_y0.get()
            # x_n= +- inf
            if (ent_xn.get() == "inf"):
                x_n = grid_x
            elif (ent_xn.get() == "-inf"):
                x_n = 0-grid_x
            else:
                x_n = ent_xn.get()
            # y_n = +- inf
            if (ent_yn.get() == "inf"):
                y_n = grid_y
            elif (ent_yn.get() == "-inf"):
                y_n = 0-grid_y
            else:
                y_n = ent_yn.get()
            
            file_obj.write("2 " + str(x_0) + " " + str(y_0) + " " + str(x_n) + " " + str(y_n) + " " + ent_pot.get() + "\n")

            # destroy the widgets
            ent_x0.destroy(), ent_y0.destroy(), ent_xn.destroy(), ent_yn.destroy(), ent_pot.destroy()
            line_label.destroy(), exp_label.destroy(), start_coor.destroy(), end_coor.destroy(), pot.destroy(), done.destroy(),exit_btn.destroy(), mess.destroy()

            # runing the GUI again
            shape_inputs(grid1)
            # draw on canvas
            drawing(2,grid1,float(x_0),float(y_0),float(x_n),float(y_n))
            
        else:
            # message about filling entries
            mess = Label(master, text= "All entries need values.")
            mess.grid(row=7, column=5,columnspan=2)
            
    elif index == 3: # Rectangle
        if (len(ent_x0.get()) != 0 and len(ent_y0.get()) != 0 and len(ent_dx.get()) != 0 and len(ent_dy.get()) != 0 and len(ent_pot.get()) != 0):
            x_0 = ent_x0.get()
            y_0 = ent_y0.get()
            dx = ent_dx.get()
            dy = ent_dy.get()
            
            file_obj.write("3 " + str(x_0) + " " + str(y_0) + " " + str(dx) + " " + str(dy) + " " + ent_pot.get() + "\n")

            # destroy the widgets
            ent_x0.destroy(), ent_y0.destroy(), ent_dx.destroy(), ent_dy.destroy(), ent_pot.destroy()
            rec_label.destroy(), start_coor.destroy(), side_length.destroy(), pot.destroy(), done.destroy(),exit_btn.destroy(), mess.destroy()

            # runing the GUI again
            shape_inputs(grid1)
            # draw on canvas
            drawing(3,grid1,float(x_0),float(y_0),float(dx),float(dy))

        else:
            # message about filling entries
            mess = Label(master, text= "All entries need values.")
            mess.grid(row=7, column=5,columnspan=2)
        
    elif index == 4: # Point
        if (len(ent_x0.get()) != 0 and len(ent_y0.get()) != 0 and len(ent_pot.get()) != 0):
            # getting values from entries
            x_0 = ent_x0.get()
            y_0 = ent_y0.get()
            
            file_obj.write("4 " + str(x_0) + " " + str(y_0) + " " + ent_pot.get() + "\n")

            # destroy the widgets
            ent_x0.destroy(), ent_y0.destroy(), ent_pot.destroy()
            point_label.destroy(), start_coor.destroy(), pot.destroy(), done.destroy(),exit_btn.destroy(), mess.destroy()

            # runing the GUI again
            shape_inputs(grid1)
            # draw on canvas
            drawing(4,grid1,float(x_0),float(y_0),float(x_0),float(y_0))


        else:
            # message about filling entries
            mess = Label(master, text= "All entries need values.")
            mess.grid(row=5, column=5,columnspan=2)


# --- Drawing on Canvas
def drawing(*arg):
    # The function will take in a list of arguments, the first one being an index value indicating geometric shape, second is the grid
    # the canvas is arranged so that (0,0) is the left-hand upper corner, x increases as you travel right and y increases if you travel down.
    # The coordinate system is arranged so that the origin (0,0) will have coordinates (canvas_width/2, canvas_height/2).
    # hence generally if you want a certain coordinate you will need to use the following equation
    #   Y = (canvas_heigth/2)*(1-y/grid_y) and X = (canvas_width/2)*(1+x/grid_x)
    global grid1
    
    if (arg[0] == 1):
        # arg[2] = x_0, arg[3] = y_0, arg[4] = r
        # we create two points on the circle;
        x_1 = (canvas_width/2)*(1+ (arg[2]-arg[4])/grid_x) # coordinate is x= x_0 - r
        y_1 = (canvas_height/2)*(1 - (arg[3]-arg[4])/grid_y) # coordinate is y= y_0 - r
        x_2 = (canvas_width/2)*(1+ (arg[2]+arg[4])/grid_x) # coordinate is x= x_0 + r
        y_2 = (canvas_width/2)*(1 - (arg[3]+arg[4])/grid_x) # coordinate is y= y_0 + r
        
        arg[1].create_oval(x_1,y_1,x_2,y_2, fill="")
        
    elif (arg[0] == 2):
        # arg[2] = x_0, arg[3] = y_0, arg[4] = x_n, arg[5] = y_n
        x_1 = (canvas_width/2)*(1+ arg[2]/grid_x)
        y_1 = (canvas_height/2)*(1 - arg[3]/grid_y) #minus because of flipped coordinates for y
        x_2 = (canvas_width/2)*(1+ arg[4]/grid_x)
        y_2 = (canvas_height/2)*(1 - arg[5]/grid_y) 
        
        arg[1].create_line(x_1,y_1,x_2,y_2)
    
    elif (arg[0] == 3):
        # arg[2] = x_0, arg[3] = y_0, arg[4] = x-sidelength, arg[5] = y-sidelength
        # we use the left-hand upper corner and the right-hand bottom corner
        x_1 = (canvas_width/2)*(1+ arg[2]/grid_x)
        y_1 = (canvas_height/2)*(1 - arg[3]/grid_y)
        x_2 = (canvas_width/2)*(1+ (arg[2]+arg[4])/grid_x)
        y_2 = (canvas_height/2)*(1 - (arg[3]-arg[5])/grid_y)

        arg[1].create_rectangle(x_1,y_1,x_2,y_2)
        
        
    elif (arg[0] == 4):
        # arg[2] = x_0, arg[3] = y_0
        # we create a circle with the same two coordinates
        x_1 = (canvas_width/2)*(1+ arg[2]/grid_x)
        y_1 = (canvas_height/2)*(1 - arg[3]/grid_y)
        
        arg[1].create_oval(x_1,y_1,x_1,y_1,width=0.2, fill = 'white')
        

# --- Getting geometric shapes
def shape_inputs(grid1):
    # -- Variables
    global canvas_height, canvas_width, geo_shape, circle_btn, line_btn, rec_btn, pnt_btn, exit_btn, done
    #global grid1
    
    # Dimensions and creating layer
    canvas_width = 500
    canvas_height = 500
    #grid1 = Canvas(master,width = canvas_width,height=canvas_height,background="white")
    grid1.grid(row=1,rowspan=7,column=0,columnspan=5)

    # Coordinate System
    grid1.create_line(250,0,250,500,width=1.5)
    grid1.create_line(0,250,500,250,width=1.5)
    
    # Geometric shapes 
    geo_shape = Label(master, text="Geometric Shapes", anchor = "center", font = ("Times",18))
    geo_shape.grid(row=1,column=5,columnspan=2)
    
    # Circle
    circle_btn = Button(master, text="Circle",command=circle)
    circle_btn.grid(row=2, column=5,columnspan=2)
    
    # Line
    line_btn = Button(master, text="Line", command=line)
    line_btn.grid(row=3, column=5,columnspan=2)

    # Rectangle
    rec_btn = Button(master, text="Rectangle", command=rectangle)
    rec_btn.grid(row=4, column=5, columnspan=2)

    # Point
    pnt_btn = Button(master, text="Point", command=point)
    pnt_btn.grid(row=5, column=5, columnspan=2)
    
    # move exit button
    exit_btn.destroy()
    exit_btn = Button(master, text="Exit", command=master.destroy)
    exit_btn.grid(row=6, column=5,columnspan=2)

# --- Circle function
def circle():
    # -- Variables
    global circle_label, c_r,ent_r, centre, ent_x0,ent_y0, pot, ent_pot, exit_btn, done
    global grid1
    
    # remove previous buttons
    geo_shape.destroy(), circle_btn.destroy(), line_btn.destroy(), rec_btn.destroy(), pnt_btn.destroy()

    # Circle Label
    circle_label = Label(master, text="Circle", anchor = "center", font = ("Times",18))
    circle_label.grid(row=1,column=5,columnspan=2)
 
    # Circle Radius
    c_r = Label(master, text="Radius")
    c_r.grid(row=2,column=5)
    ent_r = Entry(master)
    ent_r.grid(row=2,column=6)

    # Circle Centre
    centre = Label(master, text="Centre Coordinates")
    centre.grid(row=3, column=5,columnspan=2)
    ent_x0 = Entry(master)
    ent_x0.grid(row=4, column=5)
    ent_y0 = Entry(master)
    ent_y0.grid(row=4, column=6)

    # Potential
    pot = Label(master, text="Potential (0 if GND)")
    pot.grid(row=5, column=5)
    ent_pot = Entry(master)
    ent_pot.grid(row=5,column=6)

    # Empty space
    mess = Label(master)
    mess.grid(row=6,columnspan=2)
    
    # Done button
    done = Button(master, text="Done", command= lambda: doneGeo(1,grid1))
    done.grid(row=7,column=5)
    
    # move exit button
    exit_btn.destroy()
    exit_btn = Button(master, text="Exit", command=master.destroy)
    exit_btn.grid(row=7, column=6)

# ---- Line Function
def line():
    # -- Variables
    global line_label, exp_label, start_coor, ent_x0,ent_y0, end_coor, ent_xn, ent_yn, pot, ent_pot, exit_btn, done
    
    # remove previous buttons
    geo_shape.destroy(), circle_btn.destroy(), line_btn.destroy(), rec_btn.destroy(), pnt_btn.destroy()

    # Line Label
    line_label = Label(master, text="Line", anchor = "center", font = ("Times",18))
    line_label.grid(row=1,column=5,columnspan=2)

    # Line explanation
    exp_label = Label(master, text="If endless lines enter inf or -inf", anchor = "center", font = ("Times",14))
    exp_label.grid(row=2,column=5,columnspan=2)
    
    # Line start coordinate
    start_coor = Label(master, text="Start Coordinates")
    start_coor.grid(row=3, column=5,columnspan=2)
    ent_x0 = Entry(master)
    ent_x0.grid(row=4, column=5)
    ent_y0 = Entry(master)
    ent_y0.grid(row=4, column=6)

    # Line end coordinate
    end_coor = Label(master, text="End Coordinates")
    end_coor.grid(row=5, column=5,columnspan=2)
    ent_xn = Entry(master)
    ent_xn.grid(row=6, column=5)
    ent_yn = Entry(master)
    ent_yn.grid(row=6, column=6)

    # Potential
    pot = Label(master, text="Potential (0 if GND)")
    pot.grid(row=7, column=5)
    ent_pot = Entry(master)
    ent_pot.grid(row=7,column=6)

    # Empty space
    mess = Label(master)
    mess.grid(row=8,columnspan=2)
    
    # Done button
    done = Button(master, text="Done", command= lambda: doneGeo(2,grid1))
    done.grid(row=9,column=5)
    
    # move exit button
    exit_btn.destroy()
    exit_btn = Button(master, text="Exit", command=master.destroy)
    exit_btn.grid(row=9, column=6)

# --- Rectangle
def rectangle():
    # -- Variables
    global rec_label, start_coor, ent_x0,ent_y0, side_length, ent_dx, ent_dy, pot, ent_pot, exit_btn, done
    
    # remove previous buttons
    geo_shape.destroy(), circle_btn.destroy(), line_btn.destroy(), rec_btn.destroy(), pnt_btn.destroy()

    # Rectangle Label
    rec_label = Label(master, text="Rectangle", anchor = "center", font = ("Times",18))
    rec_label.grid(row=1,column=5,columnspan=2)

    # Rectangle left-hand upper corner
    start_coor = Label(master, text="Left-hand Upper Corner")
    start_coor.grid(row=2, column=5,columnspan=2)
    ent_x0 = Entry(master)
    ent_x0.grid(row=3, column=5)
    ent_y0 = Entry(master)
    ent_y0.grid(row=3, column=6)

    # Rectangle Side lenghts
    side_length = Label(master, text="Side Lenghts")
    side_length.grid(row=4, column=5,columnspan=2)
    ent_dx = Entry(master)
    ent_dx.grid(row=5, column=5)
    ent_dy = Entry(master)
    ent_dy.grid(row=5, column=6)

    # Potential
    pot = Label(master, text="Potential (0 if GND)")
    pot.grid(row=6, column=5)
    ent_pot = Entry(master)
    ent_pot.grid(row=6,column=6)

    # Empty space
    mess = Label(master)
    mess.grid(row=7,columnspan=2)
    
    # Done button
    done = Button(master, text="Done", command= lambda: doneGeo(3,grid1))
    done.grid(row=8,column=5)
    
    # move exit button
    exit_btn.destroy()
    exit_btn = Button(master, text="Exit", command=master.destroy)
    exit_btn.grid(row=8, column=6)

# --- Point
def point():
    # -- Variables
    global point_label, start_coor, ent_x0,ent_y0, pot, ent_pot, exit_btn, done
    
    # remove previous buttons
    geo_shape.destroy(), circle_btn.destroy(), line_btn.destroy(), rec_btn.destroy(), pnt_btn.destroy()

    # Point Label
    point_label = Label(master, text="Point", anchor = "center", font = ("Times",18))
    point_label.grid(row=1,column=5,columnspan=2)

    # Point coordinates
    start_coor = Label(master, text="Coordinates")
    start_coor.grid(row=2, column=5,columnspan=2)
    ent_x0 = Entry(master)
    ent_x0.grid(row=3, column=5)
    ent_y0 = Entry(master)
    ent_y0.grid(row=3, column=6)

    # Potential
    pot = Label(master, text="Potential (0 if GND)")
    pot.grid(row=4, column=5)
    ent_pot = Entry(master)
    ent_pot.grid(row=4,column=6)

    # Empty space
    mess = Label(master)
    mess.grid(row=5,columnspan=2)
    
    # Done button
    done = Button(master, text="Done", command= lambda: doneGeo(4,grid1))
    done.grid(row=6,column=5)
    
    # move exit button
    exit_btn.destroy()
    exit_btn = Button(master, text="Exit", command=master.destroy)
    exit_btn.grid(row=6, column=6)

    
# ----------------- Program -------------------
# --- File
file_obj = open("conditions.txt","w")

# Top
master = Tk()
    
# Title
Title = Label(master, text = "Electrostatics", anchor = "center", font = ("Times",30), width = 11)
Title.grid(columnspan=6)

# ----- Getting grid size -----
# x-range
x_range = Label(master, text = "x-range ( -x to x )")
x_range.grid(row=1,columnspan=6)
ent_x = Entry(master)
ent_x.grid(row=2,columnspan=6)

# x-step size
dx = Label(master, text = "Step Size in x")
dx.grid(row=3,columnspan=6)
ent_dx = Entry(master)
ent_dx.grid(row=4, columnspan=6)

# y-range
y_range = Label(master, text = "y-range ( -y to y )")
y_range.grid(row=5,columnspan=6)
ent_y = Entry(master)
ent_y.grid(row=6,columnspan=6)

# y-step size
dy = Label(master, text = "Step Size in y")
dy.grid(row=7,columnspan=6)
ent_dy = Entry(master)
ent_dy.grid(row=8, columnspan=6)

# Empty space
mess = Label(master)
mess.grid(row=9,rowspan=2,columnspan=6)

# Exit button
exit_btn = Button(master, text="Exit", command=master.destroy)
exit_btn.grid(row=11,column=3,columnspan=3)

# grid
canvas_width = 500
canvas_height = 500
grid1 = Canvas(master,width = canvas_width,height=canvas_height,background="white")

# Done button
done = Button(master,text = "Done")
done = Button(master, text = "Done", command=lambda: doneGrid(grid1,ent_x,ent_dx,ent_y,ent_dy,x_range,dx,y_range,dy,done,exit_btn,mess))
done.grid(row=11,column=0,columnspan=3)

# Run it
master.mainloop()

# Close file
file_obj.close()
