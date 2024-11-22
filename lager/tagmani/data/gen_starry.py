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
n = int(cmdlinearg('n'))
k = int(cmdlinearg("k"))
num_weights = 3
traintime = int(cmdlinearg("traintime"))
p = float(cmdlinearg("p"))
late_trains = int(cmdlinearg("latetrains", 0))

edges = []

for i in range(n-1):
    edges.append((rand(1,max(1, int((i+1)**p))), i+2))

nodes = set(node for edge in edges for node in edge)

shuffled_nodes = list(nodes)
random.shuffle(shuffled_nodes)

node_mapping = dict(zip(nodes, shuffled_nodes))

edges = [(node_mapping[edge[0]], node_mapping[edge[1]]) for edge in edges]


print(n, k)

weights = []
for i in range(num_weights):
    weights.append(int(pow(9.69, rand(1, 3))))


tot_dist = 0
for e in edges:
    d = random.choice(weights)
    tot_dist += d
    print(e[0], e[1], d)


seen_times = set()
for i in range(k):
    while 1:
        time = rand(0, traintime*n)
        if late_trains:
            time += tot_dist + 20
        if time in seen_times:
            continue
        seen_times.add(time)
        a = rand(1,n)
        b = rand(1,n)
        while b==a:
            b = rand(1,n)
        print(a, b, time, rand(1, traintime))
        break
