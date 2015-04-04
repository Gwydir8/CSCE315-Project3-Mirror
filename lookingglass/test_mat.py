import sys

import matplotlib.pyplot as plt

colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']
#set of all population's set of x's and y's
all_populations_x = []
all_populations_y = []

def main():
    """Takes two arguments: filename to read in from, and the second is sample rate
    
    Sample Rate example: if you're giving 1 per 30 points, type 30
    if you're giving every data point, type 1
    """
    fname = "test.txt" if len(sys.argv) < 1 else sys.argv[1]
    data = readData(fname)
    parseData(data)
    drawWindow()

def readData(fname):
    """Reads file given by fname. Throws ioerror if file doesn't exist"""
    try:
        f = open(fname, 'r')
    except IOError:
        print 'cannot open', fname
    else:
        global steps
        steps = []
        data = f.read()
    data = data.split('\n')
    data.pop() #python is storing last newline
    f.close()
    return data
def parseData(data):
    """Takes a set of data and adds to population.. Reads '-' as sign for another population"""
    sample_rate = 1
    if len(sys.argv) > 2:
        sample_rate = sys.argv[2]
    global all_populations_x, all_populations_y
    x, y = [], []
    independent = 0
    for row in data:
        independent += int(sample_rate)
        if row == "-":
            all_populations_x.append(x)
            all_populations_y.append(y)
            x , y = [], []
        try:
            y.append(float(row))
            x.append(independent)
        except ValueError:
            pass


def drawWindow():
    """Draws all of the different populations in a range of colors"""
    global all_populations_x, all_populations_y, colors
    fig = plt.figure()

    ax1 = fig.add_subplot(111)

    ax1.set_title("Genetic Progress")
    ax1.set_xlabel('Number of circuits')
    ax1.set_ylabel('Fitness')

    for i in range(len(all_populations_x)):
        color = float(i) / len(all_populations_x)
        ax1.plot(all_populations_x[i], all_populations_y[i], colors[i % 7], label=('Population #' + str(i)))

    legend = ax1.legend()

    plt.show()


if __name__ == "__main__":
    main()
