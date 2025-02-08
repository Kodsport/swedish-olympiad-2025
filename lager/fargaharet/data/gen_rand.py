#!/usr/bin/python3

import sys
import random
import math
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
q = int(cmdlinearg('q'))
maxv = int(cmdlinearg('maxv'))

mode = cmdlinearg('mode','distinct')

print(n,q)
arr = [random.randint(0, maxv) for i in range(n)]
print(*arr)

while q:
    a,b = randint(1,n), randint(0, maxv)
    if mode == 'distinct' and arr[a-1] == b:
        continue
    arr[a-1] = b
    q -= 1
    print(a,b)

