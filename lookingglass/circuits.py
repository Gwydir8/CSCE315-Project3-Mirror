import math
from graphics import *
def dot(x, y):
    dot = Circle(Point(x, y), 2)
    dot.setFill("black")
    return dot

def not_gate(x, y):
    not_gate = Polygon([Point(x, y), \
                        Point(x + 30, y), Point(x + 15, y + 30)])

    not_gate.setFill("red")
    return not_gate


def and_gate(x, y):
    pts = [Point(x + 30, y), Point(x, y)]
    for i in xrange(30):
        if i <= 15:
            temp_y = math.sqrt(1 - pow((30-i)/30.0, 2))
            pts.append(Point(x + i, y + temp_y * 30))
        else:
            temp_y = math.sqrt(1 - pow(i/30.0, 2))
            pts.append(Point(x + i, y + temp_y * 30))

    and_gate = Polygon(pts)
    and_gate.setFill("blue")
    return and_gate


def or_gate(x, y):
    pts = [Point(x, y)]
    #drawing base
    for i in xrange(31):
        if i <= 15:
            temp_y = math.sqrt(1 - pow((30-i)/30.0, 2))
            pts.append(Point(x + i, y + temp_y * 10))
        else:
            temp_y = math.sqrt(1 - pow(i/30.0, 2))
            pts.append(Point(x + i, y + temp_y * 10))
    #drawing top
    for i in reversed(xrange(30)):
        if i <= 15:
            temp_y = math.sqrt(1 - pow((30-i)/30.0, 2))
            pts.append(Point(x + i, y + temp_y * 30))
        else:
            temp_y = math.sqrt(1 - pow(i/30.0, 2))
            pts.append(Point(x + i, y + temp_y * 30))

    or_gate = Polygon(pts)
    or_gate.setFill("green")
    return or_gate

