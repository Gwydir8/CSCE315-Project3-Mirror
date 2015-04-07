import matplotlib.pyplot as plt
from numpy.random import rand

prev_steps = -1

steps = []

for color in ['red', 'green', 'blue']:
    n = 750
    x, y = rand(2, n)
    scale = 200.0 * rand(n)
    plt.scatter(x, y, c=color, s=scale, label=color,
                alpha=0.3, edgecolors='none')

plt.legend()
plt.grid(True)

plt.show()


def readInSteps(fname):
    """Reads file given by fname. Throws error if file doesn't exist"""
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
    """Take in one argument as the file to read. Visualizes the file's steps

    Syntax for file ||  Notes
    1 NONE 1        ||  This must be the first step. You shouldn't use NONEs elsewhere
    2 NONE 2        ||  This must be the second step. Any more NONE should proceed immediately
    3 NOT 1         ||  Not gates take one argument
    4 AND 2 3       ||  And gates take two arguments
    5 OR 3 4        ||  Or gates take two arguments
    """
    global prev_steps
    while True:
        readInSteps(sys.argv[1])
        if len(steps) != prev_steps :
            canvas = Canvas()
            for i in range(len(steps)):
                if prev_steps > i:
                    pass
                elif (str(steps[i].replace(' ', '').strip()) == '1NONE1' and (i - prev_steps) > 1):
                    prev_steps = i
                    break
                else:
                    canvas.visualizeStep(steps[i])
            else:
                prev_steps = len(steps)
        time.sleep(2)

    canvas.waitForClick()

# execute only if run as a script
if __name__ == "__main__":
    main()
