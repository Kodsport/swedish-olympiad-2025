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
samerat = int(cmdlinearg('samerat', 0))
samegoal = int(cmdlinearg('samegoal', 0))


def trygen():
    edges = []
    adj = [[] for i in range(n)] 

    seen = set()

    for i in range(m):
        while 1:
            a,b=random.sample(range(0,n-1),2)
            if (a,b) in seen or (b,a) in seen:
                continue
            seen.add((a,b))
            edges.append((a,b))
            adj[a].append(b)
            adj[b].append(a)
            break

    for i in range(n):
        if len(adj[i])==1:
            return []

    for i in range(len(edges)):
        u,v = edges[i]
        a = random.choice(adj[v])
        b = random.choice(adj[u])
        
        edges[i] = (u,v,a,b)
    return edges

edges = trygen()
while len(edges)==0:
    edges=trygen()

assert len(edges)==m
print(n, len(edges), q)
for e in edges:
    print(*(i+1 for i in e))

for i in range(q):
    s,r,t=random.sample(range(1,n), 3)
    print(s,r,t)