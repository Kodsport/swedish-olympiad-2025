#!/usr/bin/python3

import sys
import random
import math
from random import randint as rand
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
r = int(cmdlinearg('r'))
c = int(cmdlinearg('c'))
q = int(cmdlinearg('q'))
p = random.random()
grid = []
unblocked_positions = []
for i in range(r):
    row = []
    for j in range(c):
        if random.random()>p:
            row.append('#')
        else:
            unblocked_positions.append((i+1,j+1))
            row.append('.')
    grid.append(row)

while len(unblocked_positions)<3:
    a,b=rand(1,r),rand(1,c)
    if (a,b) in unblocked_positions:
        continue
    if grid[a-1][b-1]=='.':
        continue
    grid[a-1][b-1]='.'
    unblocked_positions.append((a,b))

print(r, c, q)
for row in grid:
    print("".join(row))
for i in range(q):
    start, box, goal = random.sample(unblocked_positions, 3)
    print(start[0], start[1], box[0], box[1], goal[0], goal[1])