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
#m = int(cmdlinearg("m"))
t = int(cmdlinearg("t"))

maxe = int(cmdlinearg("maxe", 1e5))
maxt = int(cmdlinearg("maxt", 1e8))

root0 = int(cmdlinearg("root0",0))

edges = []

main = [0]

for i in range(1,n//2):
    main.append(i)
    edges.append((i,i-1))
    nxtind = i+1

leaves = 0

boned = [0]*len(main)

while len(edges) < n-1:
    l = rand(1,min(1000,n-1 - (len(edges))))

    b = base = random.choice(main) # välj någon bas

    for _ in range(l): #väx ut
        edges.append((base,nxtind))
        base = nxtind
        nxtind += 1
    
    leaves += 1

    while len(edges) < n-1: #om möjligt, väx ut ännu en gren
        l = min(l,n-1 - (len(edges)))
        base = b

        for _ in range(l):
            edges.append((base,nxtind))
            base = nxtind
            nxtind += 1
        
        leaves += 1

m = int(cmdlinearg("m", leaves))

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


def energydist():
    graph = [[] for _ in range(n)]

    assert(len(edges) == n-1), f"{len(edges)=}, {n=}"

    for x,y in edges:
        graph[x].append(y)
        graph[y].append(x)

    chi = [[] for _ in range(n)]
    dis = [-1]*n
    dis[0] = 0
    BFS = [0]
    for cur in BFS:
        for nei in graph[cur]:
            if dis[nei] == -1:
                chi[cur].append(nei)
                dis[nei] = dis[cur] + 1
                BFS.append(nei)
    
    e = [1]*n
    dp = [0]*n

    topo = [0]
    for cur in topo:
        topo += chi[cur]
    assert(len(topo) == n), f"{len(topo)=}"

    for cur in topo[::-1]:
        if len(chi[cur]) == 0:
            dp[cur] = e[cur]
            continue
        
        e[cur] = min(maxe,sum(dp[nei] for nei in chi[cur] )) 
        dp[cur] = sum(dp[nei] for nei in chi[cur])
    
    return e


if int(cmdlinearg("specialEnergy",1)):
    energy = energydist()[1:]
else:
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