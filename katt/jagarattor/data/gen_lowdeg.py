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
m = int(cmdlinearg('m'))
q = int(cmdlinearg('q'))
maxdeg = int(cmdlinearg('maxdeg'))

def generate_graph(n, m):
    edges = set()
    degree = [0] * n
    
    while len(edges) < m:
        a, b = random.sample(range(n), 2)
        if (a, b) in edges or (b, a) in edges:
            continue
        if degree[a]==maxdeg or degree[b]==maxdeg:
            continue
        edges.add((a, b))

    return [list(edge) for edge in edges]


edges = generate_graph(n, m)
adj = [[] for i in range(n)]
for e in edges:
    a,b=e
    adj[a].append(b)
    adj[b].append(a)
for i in range(len(edges)):
    u,v = edges[i]
    a = random.choice(adj[v])
    b = random.choice(adj[u])
    
    edges[i] = (u,v,a,b)
assert len(edges)==m
print(n, len(edges), q)
for e in edges:
    print(*(i+1 for i in e))

for i in range(q):
    s,r,t=random.sample(range(1,n), 3)
    print(s,r,t)