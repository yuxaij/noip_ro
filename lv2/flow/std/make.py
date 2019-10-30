import sys
import os

if __name__ == '__main__':
    wf = open('{}.in'.format(sys.argv[1]), 'w')
    for filename in os.listdir('.'):
        if filename.endswith('{}.cs'.format(sys.argv[1])):
            print('find case: {}'.format(filename))
            with open(filename, 'r') as f:
                case = f.read()
        
            wf.write(case)

    wf.write("0 0\n")
    wf.close()

