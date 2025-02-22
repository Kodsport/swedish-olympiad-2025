#!/usr/bin/python3
# hardest testcase so far

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
q = int(cmdlinearg('q'))

def generate_graph(n):
    edges = set()
    for i in range(n//2):
        edges.add((i,i+1))
    for i in range(n//2, n):
        edges.add((i-n//2,i))

    return [i for i in edges]

edges = generate_graph(n)
adj = [[] for i in range(n)]
for e in edges:
    a,b=e
    adj[a].append(b)
    adj[b].append(a)
for i in range(len(edges)):
    u,v = edges[i]
    if 1:
        a = random.choice(list(j for j in adj[v] if j != v))
        b = v

    edges[i] = (u,v,a,b)
print(n, len(edges), q)
for e in edges:
    print(*(i+1 for i in e))

for i in range(q):
    s = 1
    r = rand(2,n//2)
    t = rand(n//2+1, n-1)
    print(s,r,t)
