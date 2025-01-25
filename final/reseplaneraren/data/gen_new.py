#!/usr/bin/python3

import sys
import random
import math
from random import randint

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

INF = 10**9

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
k = int(cmdlinearg('k'))
q = int(cmdlinearg('q'))
branch = int(cmdlinearg('branch', INF))
tram_len = int(cmdlinearg('tram_len', INF))
mode = cmdlinearg('mode', 'random')

edges = []
trams = []
queries = []

if mode == "random":
    for i in range(1, n):
        lim = max(0, i-branch)
        p = random.randrange(lim, i)
        edges.append((p, i))
    for _ in range(k):
        i = random.randrange(1, n)
        lim = max(0, i-tram_len)
        j = random.randrange(lim, i)
        trams.append((i, j))
    for _ in range(q):
        u, v = random.sample(range(n), 2)
        queries.append((u, v))
elif mode == "star":
    noise = int(cmdlinearg('noise', 0))
    for i in range(1, n-noise):
        edges.append((0, i))
    for i in range(n-noise, n):
        edges.append((i, random.randrange(0,i)))
    for i in range(k-noise):
        trams.append((0, random.randrange(1, n)))
    for i in range(noise):
        u, v = random.sample(range(n), 2)
        trams.append((u, v))
    for _ in range(q):
        u, v = random.sample(range(n), 2)
        queries.append((u, v))


print(n, len(trams), len(queries))

for u, v in edges:
    print(u+1,v+1)

for u, v in trams:
    print(u+1,v+1)

for u, v in queries:
    print(u+1,v+1)
    

