
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

mat = [[-1]*cols for r in range(rows)]

n = 1
for r in range(rows):
    c = 0
    while c < cols:
        while c < cols:
            mat[r][c] = n
            c += 1
            if random.randint(0, 1):
                break
        n += 1

n -= 1
perm = [i for i in range(n)]
random.shuffle(perm)

for r in range(rows):
    for c in range(cols):
        mat[r][c] = perm[mat[r][c]-1]+1

print(n, rows, cols)
for row in mat:
    print(*row)