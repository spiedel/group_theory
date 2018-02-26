from Tkinter import *

# -------- Variables --------
"""
master = tkinter window
Title = Title for GUI
"""
# ------- Functions --------
# -- Done Button 1
# this is for after getting x and y range
def doneGrid(*arg):
    global mess
    
    if (len(arg[0].get()) != 0 and len(arg[1].get()) != 0 and len(arg[2].get()) != 0 and len(arg[3].get()) !=0 ):
        file_obj.write(arg[0].get() + " " + arg[1].get() + " " + arg[2].get() + " " + arg[3].get() + "\n")

        # Remove everything by destroying it
        for a in arg:
            a.destroy()
        
        # Running next step
        shape_inputs()
    else:
        # message about filling entries
        mess = Label(master, text="All entries need values.")
        mess.grid(row=9,columnspan=6)

def doneGeo(index):
    global mess, done

    if index == 1: # Circle
        if (len(ent_r.get()) != 0 and len(ent_x0.get()) != 0 and len(ent_y0.get()) != 0 and len(ent_pot.get()) != 0):
            file_obj.write("1 " + ent_r.get() + " " + ent_x0.get() + " " + ent_y0.get() + " " + ent_pot.get() + "\n")

            # detroy the widgets
            ent_r.destroy(),ent_x0.destroy(),ent_y0.destroy(),ent_pot.destroy()
            c_r.destroy(), centre.destroy(), pot.destroy(), done.destroy(), exit_btn.destroy(), mess.destroy()

            # runing the GUI again
            shape_inputs()
        else:
            # message about filling entries
            mess = Label(master, text= "All entries need values.")
            mess.grid(row=6, column=5,columnspan=2)
        
    #elif index == 2: # Line
        #if (len(ent_x0.get()) != 0 and len(ent_y0.get()) != 0 and len(ent_xn.get()) != 0 and len(ent_yn.get()) != 0 and len(ent_pot.get()) != 0):
         #   file_obj.write("2 " + ent_x0.get() + " " + ent_y0.get() + " " + ent_xn.get() + " " + ent_yn.get() + " " + ent_pot.get() + "\n")

            # destroy the widgets
          #  ent_x0.destroy(), ent_y0.destroy(), ent_xn.destroy(), ent_yn.destroy(), ent_pot.destroy()
           # line_label, exit_ btn.destroy(), mess.destroy()
            
    #elif index == 3: # Rectangle
            
    #elif index == 4: # Point
                
# --- Getting geometric shapes
def shape_inputs():
    # -- Variables
    global canvas_height, canvas_width, grid1, geo_shape, circle_btn, line_btn, rec_btn, pnt_btn, exit_btn, done
    
    # Dimensions and creating layer
    canvas_width = 500
    canvas_height = 500
    grid1 = Canvas(master,width = canvas_width,height=canvas_height,background="white")
    grid1.grid(row=1,rowspan=7,column=0,columnspan=5)


    # Coordinate System
    grid1.create_line(250,0,250,500)
    grid1.create_line(0,250,500,250)

    
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
    done = Button(master, text="Done", command= lambda: doneGeo(1))
    done.grid(row=7,column=5)
    
    # move exit button
    exit_btn.destroy()
    exit_btn = Button(master, text="Exit", command=master.destroy)
    exit_btn.grid(row=7, column=6)

# ---- Line Function
def line():
    # -- Variables
    global line_label, start_coor, ent_x0,ent_y0, end_coor, ent_xn, ent_yn, pot, ent_pot, exit_btn, done
    
    # remove previous buttons
    geo_shape.destroy(), circle_btn.destroy(), line_btn.destroy(), rec_btn.destroy(), pnt_btn.destroy()

    # Line Label
    line_label = Label(master, text="Line", anchor = "center", font = ("Times",18))
    line_label.grid(row=1,column=5,columnspan=2)

    # Line start coordinate
    start_coor = Label(master, text="Start Coordinates")
    start_coor.grid(row=2, column=5,columnspan=2)
    ent_x0 = Entry(master)
    ent_x0.grid(row=3, column=5)
    ent_y0 = Entry(master)
    ent_y0.grid(row=3, column=6)

    # Line end coordinate
    end_coor = Label(master, text="End Coordinates")
    end_coor.grid(row=4, column=5,columnspan=2)
    ent_xn = Entry(master)
    ent_xn.grid(row=5, column=5)
    ent_yn = Entry(master)
    ent_yn.grid(row=5, column=6)

    # Potential
    pot = Label(master, text="Potential (0 if GND)")
    pot.grid(row=6, column=5)
    ent_pot = Entry(master)
    ent_pot.grid(row=6,column=6)

    # Empty space
    mess = Label(master)
    mess.grid(row=7,columnspan=2)
    
    # Done button
    done = Button(master, text="Done")#, command= lambda: doneGeo())
    done.grid(row=8,column=5)
    
    # move exit button
    exit_btn.destroy()
    exit_btn = Button(master, text="Exit", command=master.destroy)
    exit_btn.grid(row=8, column=6)

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
    done = Button(master, text="Done")#, command= lambda: doneGeo())
    done.grid(row=8,column=5)
    
    # move exit button
    exit_btn.destroy()
    exit_btn = Button(master, text="Exit", command=master.destroy)
    exit_btn.grid(row=8, column=6)

# --- Rectangle
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
    done = Button(master, text="Done")#, command= lambda: doneGeo())
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

# Done button
done = Button(master,text = "Done")
done = Button(master, text = "Done", command=lambda: doneGrid(ent_x,ent_dx,ent_y,ent_dy,x_range,dx,y_range,dy,done,exit_btn,mess))
done.grid(row=11,column=0,columnspan=3)

# Run it
master.mainloop()

# Close file
file_obj.close()
