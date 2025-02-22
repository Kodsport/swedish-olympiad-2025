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
minsz = int(cmdlinearg('minsz', 1))
maxk = int(cmdlinearg("maxk", 1000000000))
same = int(cmdlinearg('same', 0))

print(n)

if same:
    r = random.randint(minsz, maxsz)
    c = random.randint(minsz, maxsz)
    for i in range(n):
        k = random.randint(1, maxk)
        print(r, c, k)
    exit(0)


for i in range(n):
    k = random.randint(1, maxk)
    print(random.randint(minsz, maxsz), random.randint(minsz, maxsz), k)

