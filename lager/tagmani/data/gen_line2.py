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
w = int(cmdlinearg("w"))
d = int(cmdlinearg("d"))

print(n, k)

weights = [rand(1, 10) for i in range(n-1)]
for i in range(n-1):
    weights[i] = rand(1, 10000)

totdist = 0
for i in range(n-1):
    d = weights[i]
    totdist += d
    print(i+1, i+2, d)


seen_times = set()
for i in range(k):
    while 1:
        time = rand(0, (i+1)*rand(1, 30))
        if time in seen_times:
            continue
        seen_times.add(time)
        a = rand(1,n)
        while 1:
            b = a+rand(1,d)
            if b==a or b < 1 or b > n:
                continue
            break
        print(a, b, time, rand(1, rand(1, 100)))
        break
