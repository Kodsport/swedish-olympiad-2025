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
n = int(cmdlinearg('n'))
k = int(cmdlinearg("k"))
num_weights = int(cmdlinearg("num_weights"))
traintime = int(cmdlinearg("traintime"))
max_exp=int(cmdlinearg("max_exp", 9))


print(n, k)

weights = []
for i in range(num_weights):
    weights.append(int(pow(9.69, rand(1, max_exp))))

totdist = 0
for i in range(n-1):
    d = random.choice(weights)
    totdist += d
    print(i+1, i+2, d)


seen_times = set()
for i in range(k):
    while 1:
        time = rand(0, traintime*n)
        if time in seen_times:
            continue
        seen_times.add(time)
        a = rand(1,n)
        b = rand(1,n)
        while b==a:
            b = rand(1,n)
        print(a, b, time, rand(1, traintime))
        break
