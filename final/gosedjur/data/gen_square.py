#!/usr/bin/python3

import sys
import random
import math
from random import randint
from string import ascii_lowercase

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

rows = int(cmdlinearg('r'))
cols = int(cmdlinearg('c'))

mat = [[-1 for c in range(cols)] for r in range(rows)]
unfilled = rows * cols
n = 1

iters = 0
while unfilled > 0 and iters < 100000:
    iters += 1
    r = random.randint(0, rows-1)
    c = random.randint(0, cols-1)
    if mat[r][c] != -1: continue

    def test(R, C):
        if R >= rows: return False
        if C >= cols: return False
        for r_ in range(r, R+1):
            for c_ in range(c, C+1):
                if mat[r_][c_] != -1: return False
        return True
    
    R = r
    C = c
    while True:
        if random.randint(0, 4) == 0: 
            break
        if random.randint(0, 2) == 0:
            if test(R + 1, C):
                R += 1
        if random.randint(0, 1) == 0:
            if test(R, C + 1):
                C += 1
    
    for r_ in range(r, R+1):
        for c_ in range(c, C+1):
            mat[r_][c_] = n
            unfilled -= 1
    n += 1

for r in range(rows):
    for c in range(cols):
        if mat[r][c] == -1:
            mat[r][c] = n
            n += 1

n -= 1


print(n, rows, cols)
for row in mat:
    print(*row)