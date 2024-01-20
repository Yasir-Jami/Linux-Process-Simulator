#!/usr/bin/python3
from graphics import *
from PIL import Image as otherImage
import sys
import os.path
filename = "logfile"
displayWidth = 500


def main():
    data = getData(filename)
    widths = getWidths(data, displayWidth)
    colours = []
    for width in widths:
        colours.append(generateColour(width))
    #file = open("lab02/log/") #  use for SS
    #file = open(os.path.dirname(__file__)+"\..\log")
    file = open(filename)
    win = GraphWin("output", 700, 300)
    buffer = 100
    i = 0
    for dat in data:
        rect = Rectangle(Point(buffer,100),Point(buffer+(widths[i]),200))
        buffer += widths[i]
        rect.setFill(colours[i])
        rect.draw(win)
        i += 1
    #win.setBackground(color_rgb(r,g,b))
    win.getMouse()
    #img = Image()
    #Image.save(img,"file.png")
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
    
    return [[100,7610],[50,9934],[10,2876]]
 
def generateColour(num):
    r = int(num%255)
    g = int(255 - r)
    b = int(num**2%255)
    return color_rgb(r,g,b)
