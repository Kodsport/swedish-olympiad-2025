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
q = int(cmdlinearg('q'))
samerat = int(cmdlinearg('samerat', 0))
samestart = int(cmdlinearg('samestart', 0))
samegoal = int(cmdlinearg('samegoal', 0))

def generate_graph(n):
    edges = set()
    for i in range(1,n):
        edges.add((0,i))

    return [i for i in edges]

edges = generate_graph(n)
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
print(n, len(edges), q)
for e in edges:
    print(*(i+1 for i in e))

def unique_choice(choices):
    while True:
        pos = random.randint(1,n)
        if pos not in choices:
            return pos

sames, samer, sameg = random.sample(range(1,n+1),3)
for i in range(q):
    if samestart:
        s = sames
    else:
        s = unique_choice([])
    if samerat:
        r = samer
    else:
        r = unique_choice([s])
    if samegoal:
        t = sameg
        r = unique_choice([t])
        s = unique_choice([t,r])
    else:
        t = unique_choice([s,r])
    
    print(s,r,t)
