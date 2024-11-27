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
n = int(cmdlinearg('n'))
rows = int(cmdlinearg('r'))
cols = int(cmdlinearg('c'))

mat = [[-1]*cols for r in range(rows)]

def nei(r, c):
    for R, C in [[r +1, c], [r, c+1], [r-1, c], [r, c-1]]:
        if 0 <= R < rows and 0 <= C < cols:
            yield R, C

x = 1
for r in range(rows):
    for c in range(cols):
        if mat[r][c] != -1:
            continue
        if x == n:
            mat[r][c] = x
            continue
        
        q = [[r, c]]
        mat[r][c] = x
        while q:
            if (random.randint(0,10) == 0):
                break
            i = random.randint(0, len(q)-1)
            R, C = q[i]
            q.pop(i)

            mat[R][C] = x

            for dr, dc in nei(R, C):
                if mat[dr][dc] == -1:
                    q.append([dr, dc])
        x += 1

n = 0
for r in range(rows):
    n = max(n, max(mat[r]))
#    for c in range(cols):
#        mat[r][c] = f"{mat[r][c]:<3}"
print(n, rows, cols)
for r in range(rows):
    print(*mat[r])

