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
print(n)

target = int(cmdlinearg('target'))
assert target < 1e11

for i in range(n):
    r = random.randint(100, 1000000)
    while (target // r > 900000): 
        r = random.randint(100, 1000000)

    c = target // r
    c = random.randint(c - 10, c + 10)
    c = max(min(c, 1000000), 1)

    print(r, c)

