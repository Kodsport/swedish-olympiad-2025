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
samebox = int(cmdlinearg('samebox', 0))
samegoal = int(cmdlinearg('samegoal', 0))
snake = int(cmdlinearg('snake', 0))
pockets = int(cmdlinearg('pockets', 0))

p = random.random()
grid = []
unblocked_positions = []
for i in range(r):
    row = []
    if snake:
        for j in range(c):
            if i%2 == 0 and ((j>0 and j<c-1) or (i%4==0 and j==0) or (i%4==2 and j==c-1)):
                row.append('#')
            else:
                unblocked_positions.append((i+1,j+1))
                row.append('.')
    elif pockets:
        for j in range(c):
            if (i//pockets+j)%2 == 0:
                row.append('#')
            else:
                unblocked_positions.append((i+1,j+1))
                row.append('.')
    else:
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

def unique_choice(choices):
    while True:
        pos = random.choice(unblocked_positions)
        if pos not in choices:
            return pos

sbox, sgoal = random.sample(unblocked_positions, 2)
for i in range(q):
    if samegoal:
        goal = sgoal
    else:
        goal = unique_choice([])
    if samebox:
        box = sbox
    else:
        box = unique_choice([goal])
    
    start = unique_choice([box, goal])
    print(start[0], start[1], box[0], box[1], goal[0], goal[1])