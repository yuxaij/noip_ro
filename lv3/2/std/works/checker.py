import os
import sys

os.system('g++ -o std std.cpp -O2')

for i in range(1, 21):
    print('round {}...'.format(i))

    os.system('./std <{}.in >{}.ans 2>/tmp/null'.format(i, i))
    for j in range(10):
        print(j)
        os.system('./std <{}.in >{}_2.out 2>/tmp/null'.format(i, i))
        if os.system('diff {}.ans {}_2.out'.format(i, i)):
            sys.exit(0)

    os.system('rm {}_2.out'.format(i))
