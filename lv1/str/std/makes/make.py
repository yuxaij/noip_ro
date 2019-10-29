import os, sys
import numpy as np
import random
import string
from argparse import ArgumentParser


tmpfile = '/tmp/str_data_gen.tmp'

def dst(x):
    return type(x)(x * (1 - np.random.rand() * 0.1))

def read_from(tmp):
    with open(tmpfile, 'r') as f:
        s = f.read()
    return s

def normal(limit):
    limit = dst(limit)
    ksize = np.random.randint(4) + 2
    rep = ''.join(random.sample(string.ascii_lowercase, np.random.randint(5) + 1))
    os.system('./gen_normal {} {} {} >{}'.format(limit, ksize, rep, tmpfile))

    return read_from(tmpfile)

def kill_hash(mode):
    os.system('./gen_kill_hash {} >{}'.format(mode, tmpfile))
    return read_from(tmpfile)

def onerep_ab(n, k):
    os.system('./gen_onerep_ab {} {} >{}'.format(dst(n), k, tmpfile))
    return read_from(tmpfile)

def onlyone(n, k):
    os.system('./gen_onlyone {} {} >{}'.format(dst(n), k, tmpfile))
    return read_from(tmpfile)

def reprep_ab(n, k):
    os.system('./gen_reprep_ab {} {} >{}'.format(dst(n), k, tmpfile))
    return read_from(tmpfile)

def reprep_all(n, k):
    os.system('./gen_reprep_all {} {} >{}'.format(dst(n), k, tmpfile))
    return read_from(tmpfile)

if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument('n', type=int)
    parser.add_argument('output', type=str)
    parser.add_argument('cases', nargs='+', type=str)
    
    args = parser.parse_args()

    for name in ['kill_hash', 'onerep_ab', 'onlyone', 'normal', 'reprep_ab', 'reprep_all']:
        if not os.path.exists('gen_{}'.format(name)):
            os.system('g++ -o gen_{} gen_{}.cpp -O2'.format(name, name))
        elif args.n == 0:
            os.remove('gen_{}'.format(name))

    if args.n == 0:
        sys.exit(0)

    s = []
    for i in range(5):
        for case in args.cases:
            if case == 'normal':
                s.append(normal(args.n))
            elif case.startswith('kill_hash'):
                s.append(kill_hash(case[-1]))
            elif case.startswith('onerep_ab'):
                s.append(onerep_ab(args.n, case[9:]))
            elif case.startswith('onlyone'):
                s.append(onlyone(args.n, case[7:]))
            elif case.startswith('reprep_ab'):
                s.append(reprep_ab(args.n, case[9:]))
            elif case.startswith('reprep_all'):
                s.append(reprep_all(args.n, case[10:]))

    s = [t if t[-1] != '\n' else t[:-1] for t in s]
    s.append('0')

    with open(args.output, 'w') as f:
        f.write('\n'.join(s))
