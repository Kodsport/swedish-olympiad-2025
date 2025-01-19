#!/usr/bin/python3

import sys
import random
from random import randint

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))  
m = int(cmdlinearg('m'))  
max_duck = int(cmdlinearg('max_duck', 10**18)) 
max_duck_sum = int(cmdlinearg('max_duck_sum', -1)) 
c_is_i = int(cmdlinearg('c_is_i', 0))

print(n, m)

ducks = [randint(0, max_duck) for _ in range(n)]
if max_duck_sum != -1:
    curr_sum = sum(ducks)
    if curr_sum > max_duck_sum:
        scale = max_duck_sum / curr_sum
        ducks = [int(d * scale) for d in ducks]

print(*ducks)

if c_is_i:
    colors = [i+1 for i in range(m)]
else:
    colors = [randint(1, n) for _ in range(m)]
print(*colors)