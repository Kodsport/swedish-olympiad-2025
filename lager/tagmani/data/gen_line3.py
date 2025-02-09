#!/usr/bin/python3

import sys
import random
import math
from random import randint as rand

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(1e5)
k = int(1e5)

print(n, k)

border = 69696
weights = [rand(1, 10) for i in range(n-1)]
weights[border] = 1000000

totdist = 0
for i in range(n-1):
    d = weights[i]
    totdist += d
    print(i+1, i+2, d)

print(69696+123, 69696-123, 69, 1337)
seen_times = set()
seen_times.add(69696+123)
for i in range(k-1):
    while 1:
        time = rand(0, (i+1)*rand(1, 30))
        if time in seen_times:
            continue
        seen_times.add(time)
        a = rand(1,border-100)
        while 1:
            b = a+rand(-25,25)
            if b==a or b < 1 or b > n:
                continue
            break
        print(a, b, time, rand(1, rand(1, 100)))
        break
