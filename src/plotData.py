from graphics import *
from PIL import Image as otherImage
import sys
import os.path
filename = "../log/logfile*"
displayWidth = 500


def main():
    file = open(filename)
    data = getData(file)
    widths = getWidths(data, displayWidth)
    colours = []
    for dat in data:
        colours.append(generateColour(dat[1]))
    #file = open("lab02/log/") #  use for SS
    #file = open(os.path.dirname(__file__)+"\..\log")
    win = GraphWin("output", 700, 300)
    buffer = 100
    i = 0
    for i in range(len(widths)):
        #if data[i][2] != '1':
        rect = Rectangle(Point(buffer,100),Point(buffer+(widths[i]),200))
        tex=Text(Point(buffer+(widths[i]/2),150), data[i][1])
        buffer += widths[i]
        rect.setFill(colours[i])
        rect.draw(win)
        tex.draw(win)
            #i += 1
    
    aTt = Text(Point(displayWidth/2,15),"Mean Turnaround Time: "+str(getAvgTt(data)))    
    aRt = Text(Point(displayWidth/2,30),"Mean Response Time: "+str(getAvgRt(data)))
    count = Text(Point(displayWidth/2,45),"Number of processes: "+str(getAmtProcs(data)))
    
    aTt.draw(win)
    aRt.draw(win)
    count.draw(win)
    
    
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
        if dat[2] != '1':
            totalTime += (dat[0])
    ratio = maxWidth / totalTime
    
    
    
    widths = []
    
    runningproc = ''
    currentStep = 0
    
    for dat in data:
        
        if dat[2] != '1':
            if dat[1] == runningproc:
                widths[-1] += (dat[0]*ratio)
            else:
                widths.append(dat[0]*ratio)
            
            runningproc = dat[1]
    
    
    return widths
    

 
def getData(file):
    procs = []
    for line in file:
        numbers = line.split(", ")
        for i in range(2):
            numbers[i] = float(numbers[i])
        
        procs.append(numbers)
            
    return procs
 
 
 
def generateColour(num):
    r = int(num%3%255)
    g = int(255 - 1/(r+1))
    b = int(num**2%255%5)
    if num % 3 == 0:
        return color_rgb(r,g,b)
    if num%5 == 0:
        return color_rgb(b,r,g)
    return color_rgb(g,b,r)

def getAmtProcs(array):
    pids = []
    for arr in array:
        if arr[1] not in pids:
            pids.append(arr[1])
    return len(pids)

def getAvgTt(array):
    pids = []
    gT = array[0][0]
    summa = 0         # i apologize for how painfully inelegant this solution is
    for arr in array:
        if arr[1] not in pids:
            pids.append(arr[1])
        if arr[2] == '3':
            summa += (arr[0]-gT)
    return (summa / len(pids))

def getAvgRt(array):
    pids = []
    
    gT = array[0][0]
    summa = 0
    for arr in array: 
        if arr[1] not in pids:
            pids.append(arr[1])

    for pid in pids:
        for arr in array:
            if arr[1] == pid and arr[2] == '2':
                summa += (arr[0]-gT)
                break
            
    return (summa / len(pids))
