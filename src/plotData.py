from graphics import *
from PIL import Image as otherImage
import sys
import os.path
filename = "log"
displayWidth = 500


def main():
    file = open("../log/log*", "r")
    data = getData(file)
    widths = getWidths(data, displayWidth)
    colours = []
    for dat in data:
        colours.append(generateColour(dat[1]))
    win = GraphWin("output", 700, 300)
    buffer = 100
    i = 0
    for dat in data:
        rect = Rectangle(Point(buffer,100),Point(buffer+(widths[i]),200))
        tex=Text(Point(buffer+(widths[i]/2),150), dat[1])
        buffer += widths[i]
        rect.setFill(colours[i])
        rect.draw(win)
        tex.draw(win)
        i += 1
    win.getMouse()
    win.close()
    win.postscript(win = "file.eps")
    img = otherImage.open("file.eps")
    img.save("logfile.png", "png")


def getWidths(data, maxWidth):
    totalTime = 0
    for dat in data:
        totalTime += (dat[0])
    ratio = maxWidth / totalTime
    widths = []
    for dat in data:
        widths.append(dat[0]*ratio)
    return widths



def getData(file):
    procs = []
    for line in file:
        numbers = line.split(", ")
        for i in range(2):
            numbers[i] = int(numbers[i])
        procs.append(numbers)
    return procs
    #return [[100,7610],[50,9934],[10,2876]] - test suite of numbers

def generateColour(num):
    r = int(num%255)
    g = int(255 - r)
    b = int(num**2%255)
    return color_rgb(r,g,b)
