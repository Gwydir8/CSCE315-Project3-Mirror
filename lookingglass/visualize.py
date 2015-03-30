# **********************Author Info**************************
# *@author    Christopher Findeisen                         *
# *@contact    <cfindeisen7@gmail.com>                      *
# *@date     Wed 25 Mar 16:35:07 2015                       *
# ***********************************************************
import time
import string
import circuits as c
from graphics import *
prev_steps = -1
steps = []

class Canvas:
    #graphics.py window to bind to
    window = None
    #track the current state of drawing
    max_y = 1000
    max_x = 1000
    current_row = 1
    current_column = 0.0
    def __init__(self):
        global steps
        self.max_y = 45 * len(steps)
        self.window = GraphWin('Current Logic Gate', self.max_x, self.max_y) # give title and dimensions
        print "Visualizing now..."


    def visualizeStep(self, step):
        print step
        base_x = (self.current_column * 100) % (self.max_x - 50)
        base_y = self.current_row * 40
        self.setup_step(base_x, base_y)
        #first draw line
        # line =
        shapes = []
        for token in step.split():
            token = unicode(token)
            if token.isnumeric():
                num = int(token)
                if num < self.current_row:
                    offset_x = -15
                    shape = c.dot(base_x + offset_x, num * 40)
                    line_in_gate = Line(Point(base_x + offset_x, base_y - 30), \
                            Point(base_x + offset_x, num * 40) )
                    r = (20 * self.current_column) % 255
                    g = (15 * self.current_row) % 255
                    b = (140 + 10 * self.current_column) % 255
                    color = color_rgb(r, g, b)
                    line_in_gate.setFill(color)

                    line_in_gate.draw(self.window)
                    base_x += 30
                else:
                    shape = None

            if token.isalpha():
                shape_base_x = base_x - 15
                shape_base_y = base_y - 30
                if token == "NOT":
                    shape = c.not_gate(shape_base_x, shape_base_y)

                elif token == "AND":
                    #for top of and_gate
                    shape = c.and_gate(shape_base_x, shape_base_y)

                elif token == "OR":
                    shape = c.or_gate(shape_base_x, shape_base_y)

                elif token == "NONE":
                    shape = None

                else:
                    #exit?
                    print "had some problem parsing output " + token
                    raise(AttributeError)


            if shape is not None:
                shapes.append(shape)


        for shape in shapes:
            shape.draw(self.window)

        self.current_column += 1
        self.current_row += 1

    def waitForClick(self):
        self.window.getMouse() # Pause to view result
        self.window.close()

    def setup_step(self, x, y):
        #draws the horizontal line and numbers the step
        pt = Point(self.max_x - 50, y)
        step_no = Text(pt, str(self.current_row))
        step_no.setSize(14)
        step_no.draw(self.window)

        step_line = Line(Point(0, y), Point(self.max_x - 75, y))
        step_line.setWidth(2)
        step_line.draw(self.window)

    def __del__(self):
        self.window.close()

def readInSteps(fname):
    try:
        f = open(fname, 'r')
    except IOError:
        print 'cannot open', fname
    else:
        global steps 
        steps = []
        for line in f:
            steps.append(line)
        f.close()

def main():
    global prev_steps
    while True:
        readInSteps(sys.argv[1])
        if len(steps) != prev_steps :
            canvas = Canvas()
            for i in range(len(steps)):
                if prev_steps > i:
                    pass
                elif (str(steps[i].replace(' ', '').strip()) == '1NONE1' and (i - prev_steps) >= 2):
                    prev_steps = i
                    break
                else:
                    print str(steps[i].replace(' ', '')) == str('1NONE1')
                    canvas.visualizeStep(steps[i])
            else:
                print "Done reading?"
                prev_steps = len(steps)
        time.sleep(2)

    canvas.waitForClick()

# execute only if run as a script
if __name__ == "__main__":
    main()
