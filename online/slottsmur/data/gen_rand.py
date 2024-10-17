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

hi = 5#int(1e9)
print(n,q)
print(*(randint(1, hi) for i in range(n)))

for i in range(q):
    t = randint(1,2)
    if t==1:
        print(t, randint(1, n), randint(1, hi))
    else:
        l = randint(1, n)
        print(t, l, randint(l, n))
