import os

os.system("./procSim 0")
os.system("python3 plotData.py ../logfile*ALGOR_SJF")

os.system("./procSim 1")
os.system("python3 plotData.py ../logfile*ALGOR_FIFO")

os.system("./procSim 2")
os.system("python3 plotData.py ../logfile*ALGOR_RR")
