# **********************Author Info**************************
# *@author    Christopher Findeisen                         *
# *@contact    <cfindeisen7@gmail.com>                      *
# *@date     Wed 25 Mar 16:35:07 2015                       *
# ***********************************************************
import time
import math

from graphics import *
steps = []

class Canvas:
    #graphics.py window to bind to
    window = None
    #track the current state of drawing
    max_x = 1000
    max_y = 1000
    current_row = 1
    def __init__(self):
        self.window = GraphWin('Current Logic Gate', self.max_x, self.max_y) # give title and dimensions
        print "Visualizing now..."


    def visualizeStep(self, step):
        base_x = 0
        base_y = self.current_row * 50
        for token in step.split():
            token = unicode(token)
            if token.isnumeric():
                base_x += 50
            if token.isalpha():
                base_x += 50
                if token == "NOT":
                    not_gate = Polygon([Point(base_x, base_y), \
                               Point(base_x + 30, base_y), Point(base_x + 15, base_y + 30)])
                    not_gate.draw(self.window)
                elif token == "AND":
                    #for top of and_gate
                    pts = [Point(base_x + 30, base_y), Point(base_x, base_y)]
                    for i in xrange(30):
                        if i <= 15:
                            y = math.sqrt(1 - pow((30-i)/30.0, 2))
                            pts.append(Point(base_x + i, base_y + y * 30))
                        else:
                            y = math.sqrt(1 - pow(i/30.0, 2))
                            pts.append(Point(base_x + i, base_y + y * 30))

                    and_gate = Polygon(pts)
                    and_gate.draw(self.window)
                elif token == "OR":
                    pts = [Point(base_x, base_y)]
                    #drawing base
                    for i in xrange(31):
                        if i <= 15:
                            y = math.sqrt(1 - pow((30-i)/30.0, 2))
                            pts.append(Point(base_x + i, base_y + y * 15 ))
                        else:
                            y = math.sqrt(1 - pow(i/30.0, 2))
                            pts.append(Point(base_x + i, base_y + y * 15 ))
                    #drawing top
                    for i in reversed(xrange(30)):
                        if i <= 15:
                            y = math.sqrt(1 - pow((30-i)/30.0, 2))
                            pts.append(Point(base_x + i, base_y + y * 30 ))
                        else:
                            y = math.sqrt(1 - pow(i/30.0, 2))
                            pts.append(Point(base_x + i, base_y + y * 30 ))

                    or_gate = Polygon(pts)
                    or_gate.draw(self.window)


                elif token == "NONE":
                    pass
                else:
                    #exit?
                    print "had some problem parsing output " + token
                    raise(AttributeError)

        pt = Point(self.max_x - 50, base_y)
        step_no = Text(pt, str(self.current_row))
        step_no.setSize(14)
        step_no.draw(self.window)

        #go to next row
        self.current_row += 1

    def waitForClick(self):
        self.window.getMouse() # Pause to view result
        self.window.close()


def readInSteps(fname):
    try:
        f = open(fname, 'r')
    except IOError:
        print 'cannot open', fname
    else:
        global steps
        for line in f:
            steps.append(line)
        f.close()

def main():
    readInSteps(sys.argv[1])
    canvas = Canvas()
    for step in steps:
        canvas.visualizeStep(step)
    canvas.waitForClick()
#wherever the output is.

if __name__ == "__main__":
    # execute only if run as a script
    main()
