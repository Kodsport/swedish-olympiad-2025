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
q = int(cmdlinearg('q'))
c = int(cmdlinearg('c', 2))

hi = 10**9
print(n,q)
hights = [randint(1, hi) for i in range(n)]
print(*hights)


for i in range(q):
    t = randint(1,c)
    if t==2:
        while True:
            pos = randint(1, n)
            if hights[pos-1] < hi:
                break
        value = randint(1, hi-hights[pos-1])
        hights[pos-1] += value
        print(t, pos, value)
    else:
        l = randint(1, n)
        print(t, l, randint(l, n))
