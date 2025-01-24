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
    cand = [[r +1, c], [r, c+1], [r-1, c], [r, c-1]]
    random.shuffle(cand)
    for R, C in cand:
        if 0 <= R < rows and 0 <= C < cols:
            yield R, C

def get_perm():
    pos = [(r, c) for c in range(cols) for r in range(rows)]
    random.shuffle(pos)
    return pos

for i, (r, c) in enumerate(get_perm()[:n]):
    mat[r][c] = i+1

queue = []
for r, c in get_perm():
    if mat[r][c] != -1:
        for R, C in nei(r, c):
            if mat[R][C] == -1:
                queue.append((R, C))

while queue:
    random.shuffle(queue)
    new_queue = []
    iters = 5000000000000
    for r, c in queue:
        iters-=1
        if iters == 0:
            queue = queue + new_queue
            break
        if mat[r][c] != -1:
            continue

        for R, C in nei(r, c):
            if mat[R][C] != -1:
                mat[r][c] = mat[R][C]
            else:
                new_queue.append((R, C))
        
    if iters > 0:
        queue = new_queue

print(n, rows, cols)
for row in mat:
    print(*row)
