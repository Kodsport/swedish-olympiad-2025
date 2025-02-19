#!/usr/bin/python3

import sys
import random

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
maxsz = int(cmdlinearg('maxsz', 1_000_000))
same = int(cmdlinearg('same', 0))
print(n)

if same:
    r = random.randint(1, maxsz)
    c = random.randint(1, maxsz)
    for i in range(n):
        print(r, c)
    exit(0)


for i in range(n):
    print(random.randint(1, maxsz), random.randint(1, maxsz))

