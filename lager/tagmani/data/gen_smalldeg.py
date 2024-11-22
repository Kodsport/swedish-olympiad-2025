#!/usr/bin/python3

import sys
import random
import math
from random import randint as rand
import subprocess

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
k = 15000
num_weights = 3
degweights = [int(i) for i in cmdlinearg("degweights").split(",")]
traintime = 1000
edges = []

degs = [[0],[],[]]

deg = [0 for i in range(n)]

for i in range(n-1):
    while 1:
        c = random.choices([0,1,2], degweights)[0]
        if len(degs[c]):
            u = random.choice(degs[c])
            degs[c].remove(u)
            deg[i+1]+=1
            deg[u]+=1
            degs[1].append(i+1)
            if deg[u]<3:
                degs[c].append(u)
            edges.append((i+2, u+1))

            break

nodes = set(node for edge in edges for node in edge)

shuffled_nodes = list(nodes)
random.shuffle(shuffled_nodes)

node_mapping = dict(zip(nodes, shuffled_nodes))

edges = [(node_mapping[edge[0]], node_mapping[edge[1]]) for edge in edges]


print(n, k)

weights = []
for i in range(num_weights):
    weights.append(int(pow(9.69, rand(1, 3))))

for e in edges:
    print(e[0], e[1], random.choice(weights))


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
