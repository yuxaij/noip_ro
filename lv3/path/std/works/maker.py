from maker_twin_chain import gen_data as gen_to
from collections import Iterable
import numpy as np
import sys

def dst2(x):
    return type(x)((1 - 0.05 * np.random.rand()) * x)
def dst(t):
    return type(t)(dst2(x) if isinstance(x, float) or isinstance(x, int) else x for x in t)

def gen_data(filename, parts, a, b):
    if len(sys.argv) == 1 or sys.argv[1] == filename:
        gen_to(filename, parts, a, b)

metaN = ()
meta0 = (0.3, 3, 0.06, 0.03)
meta1 = (0.33333, 5, 0.06, 0.03)
meta2 = (0.2, 2, 0.03, 0.03)
meta3 = (0.4, 1, 0.06, 0.03)

gen_data('1.in', [
    dst(('chain', 100, 50, 3000, meta1)),
    dst(('random', 200, 150, 6000, metaN)),
    dst(('chain', 300, 250, 9000, meta0))
], dst2(600), dst2(300))
gen_data('2.in', [
    dst(('chain', 200, 100, 3000, meta1)),
    dst(('chain', 500, 300, 9000, meta0))
], dst2(600), dst2(300))
gen_data('3.in', [
    dst(('random', 1000, 1000, 1e9, metaN)),
], dst2(1000), dst2(100))
gen_data('4.in', [
    dst(('chain', 1000, 1000, 1e9, meta1)),
], dst2(1000), dst2(500))

gen_data('5.in', [
    dst(('random', 50000, 20000, 1e9, metaN))
], dst2(50000), -1) 
gen_data('6.in', [
    dst(('chain', 50000, 50000, 1e9, meta1))
], dst2(50000), -1)
gen_data('7.in', [
    dst(('chain', 50000, 50000, 1e9, meta0))
], dst2(50000), -1)
gen_data('8.in', [
    dst(('chain', 50000, 50000, 1e9, meta2))
], dst2(50000), -1)
gen_data('9.in', [
    dst(('chain', 50000, 50000, 1e9, meta3))
], dst2(50000), -1)

gen_data('10.in', [
    dst(('random', 100000, 100000, 1e9, metaN)),
], dst2(100000), dst2(50000)) 
gen_data('11.in', [
    dst(('chain', 50000, 45000, 1e8, meta0)),
    dst(('random', 60000, 60000, 2e8, metaN)),
    dst(('chain', 100000, 100000, 3e8, meta3))
], dst2(100000), dst2(25000)) 
gen_data('12.in', [
    dst(('random', 50000, 50000, 2e8, metaN)),
    dst(('chain', 100000, 100000, 3e8, meta3))
], dst2(100000), dst2(40000)) 
gen_data('13.in', [
    dst(('chain', 30000, 30000, 1e8, meta0)),
    dst(('chain', 60000, 60000, 2e8, meta1)),
    dst(('random', 70000, 70000, 3e8, metaN)),
    dst(('chain', 100000, 100000, 4e8, meta3))
], dst2(100000), dst2(20000)) 
gen_data('14.in', [
    dst(('chain', 30000, 30000, 1e8, meta1)),
    dst(('chain', 100000, 100000, 3e8, meta2))
], dst2(100000), dst2(50000)) 
gen_data('15.in', [
    dst(('random', 1000, 1000, 1e3, metaN)),
    dst(('chain', 50000, 60000, 1e7, meta0)),
    dst(('random', 52800, 63500, 1e8, metaN)),
    dst(('chain', 100000, 100000, 5e8, meta3))
], dst2(100000), dst2(30000)) 

gen_data('16.in', [
    dst(('chain', 500000, 500000, 1e9, meta0)),
], dst2(500000), dst2(250000)) 
gen_data('17.in', [
    dst(('chain', 150000, 150000, 1e8, meta0)),
    dst(('random', 200000, 200000, 2e8, metaN)),
    dst(('chain', 500000, 500000, 3e8, meta3))
], dst2(500000), dst2(250000)) 
gen_data('18.in', [
    dst(('chain', 100000, 100000, 1e8, meta0)),
    dst(('chain', 200000, 200000, 2e8, meta1)),
    dst(('random', 212000, 212000, 3e8, metaN)),
    dst(('chain', 500000, 500000, 4e8, meta3))
], dst2(500000), dst2(200000)) 
gen_data('19.in', [
    dst(('chain', 200000, 100000, 1e8, meta1)),
    dst(('chain', 500000, 500000, 5e8, meta2))
], dst2(500000), dst2(250000)) 
gen_data('20.in', [
    dst(('random', 30000, 30000, 1e3, metaN)),
    dst(('chain', 250000, 250000, 1e7, meta0)),
    dst(('random', 270000, 270000, 1e8, metaN)),
    dst(('chain', 500000, 500000, 5e8, meta3))
], dst2(500000), dst2(200000)) 
