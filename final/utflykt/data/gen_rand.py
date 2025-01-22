#!/usr/bin/python3

import sys
import random

INF = 10**9

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
tmax = int(cmdlinearg('tmax', 10**9))
mode = cmdlinearg('mode', 'random')

T = []

if mode == "identity":
    T = [i+1 for i in range(n)]
elif mode == "groups":
    d = int(cmdlinearg('d', n))
    distinct = random.sample(range(2, tmax+1), d)
    T = [random.choice(distinct) for _ in range(n)]
elif mode == "random":
    T = [random.randint(1,tmax) for _ in range(n)]

print(n)
for t in T:
    print(t)

