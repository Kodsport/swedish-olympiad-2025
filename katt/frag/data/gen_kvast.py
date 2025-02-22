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
m = int(cmdlinearg("m"))
t = int(cmdlinearg("t"))
l = int(cmdlinearg("l"))

ball = int(cmdlinearg("ball",n-1-l))

maxe = int(cmdlinearg("maxe", 1e5))
maxt = int(cmdlinearg("maxt", 1e8))

root0 = int(cmdlinearg("root0",0))

edges = []

ind = 1
while len(edges)<l:
    edges.append((ind-1,ind))
    ind += 1

end = ind-1

while len(edges)<l+ball:
    edges.append((ind, end))
    ind += 1

while len(edges)<n-1:
    edges.append((ind, rand(0,ind-1)))
    ind += 1

# Shuffle node labels for extra cache misses 🤤
nodes = set(node for edge in edges for node in edge)

shuffled_nodes = list(nodes)
random.shuffle(shuffled_nodes)

if root0:
    ind = shuffled_nodes.index(0)
    shuffled_nodes[0], shuffled_nodes[ind] = shuffled_nodes[ind], shuffled_nodes[0]

node_mapping = dict(zip(nodes, shuffled_nodes))

edges = [(node_mapping[edge[0]], node_mapping[edge[1]]) for edge in edges]
random.shuffle(edges)
deg = [0]*n

print(n, m, t)

weights = [random.randint(1,maxt) for _ in range(100)]
for i in range(10000):
    weights.append(int(pow(9.69, rand(1, 10))))
weights.sort()

while weights[-1] > maxt: weights.pop()

assert(len(edges) == n-1), "Not n-1 edges"
for x,y in edges:
    deg[x] += 1
    deg[y] += 1
    print(x,y,random.choice(weights))

energy = [[random.randint(1,maxe),min(maxe,random.choice(weights))][rand(0,1)] for _ in range(n-1)]
assert(len(energy) == n-1), "Not n-1 energy costs"
print(*energy)


nodes = [(deg[x],x) for x in range(1,n)]
nodes.sort()

if int(cmdlinearg("randrats",0)):
    rats = random.sample([*range(1,n)],m)
else:
    rats = [x for _,x in nodes[:m]]

assert(len(rats) == m), "Incorrect number of starting positions for rats"
print(*rats)

