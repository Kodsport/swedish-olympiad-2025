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


seen = set()

used_pos = set()
q = []
for i in range(n):
    while True:
        r = random.randint(0, rows-1)
        c = random.randint(0, cols-1)
        if (r,c) not in used_pos:
            used_pos.add((r,c))
            q.append([r, c, i+1])
            break
for r, c, i in q:
    mat[r][c] = i

while q:
    i = random.randint(0, len(q)-1)
    R, C, x = q[i]
    q.pop(i)
    if (R, C) in seen:
        continue
    seen.add((R, C))

    mat[R][C] = x
    # print(R, C, x)
    for dr, dc in nei(R, C):
        if mat[dr][dc] == -1:
            q.append([dr, dc, x])


print(n, rows, cols)
for r in range(rows):
    print(*mat[r])

