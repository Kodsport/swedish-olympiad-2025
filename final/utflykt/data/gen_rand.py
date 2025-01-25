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
elif mode == "uneven":
    large = int(cmdlinearg('large', 0))
    smalls = [random.randint(1, int(tmax ** 0.5)) for _ in range(n-large)]
    larges = [random.randint(1, tmax) for _ in range(large)]
    T = smalls+larges
    random.shuffle(T)
elif mode == "pairs":
    for i in range(n):
        if i%2 == 0:
            T.append(random.randint(1, tmax-1))
        else:
            T.append(T[-1]+1)
elif mode == "random":
    T = [random.randint(1,tmax) for _ in range(n)]

print(n)
for t in T:
    print(t)

