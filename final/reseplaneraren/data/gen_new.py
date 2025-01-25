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

g4 = int(cmdlinearg('g4',0))

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

g = [[] for _ in range(n)]
for u, v in edges:
    print(u+1,v+1)
    g[u].append(v)
    g[v].append(u)

for u, v in trams:
    print(u+1,v+1)

if g4:
    class binary_lift:
        def __init__(self, graph, data=(), f=min, root=0):
            n = len(graph)

            parent = [-1] * (n + 1)
            depth = self.depth = [-1] * n
            bfs = [root]
            depth[root] = 0
            for node in bfs:
                for nei in graph[node]:
                    if depth[nei] == -1:
                        parent[nei] = node
                        depth[nei] = depth[node] + 1
                        bfs.append(nei)

            data = self.data = [data]
            parent = self.parent = [parent]
            self.f = f

            for _ in range(max(depth).bit_length()):
                old_data = data[-1]
                old_parent = parent[-1]
                
                data.append([f(val, old_data[p]) for val,p in zip(old_data, old_parent)])
                parent.append([old_parent[p] for p in old_parent])

        def lca(self, a, b):
            depth = self.depth
            parent = self.parent

            if depth[a] < depth[b]:
                a,b = b,a
            
            d = depth[a] - depth[b]
            for i in range(d.bit_length()):
                if (d >> i) & 1:
                    a = parent[i][a]

            for i in range(depth[a].bit_length())[::-1]:
                if parent[i][a] != parent[i][b]:
                    a = parent[i][a]
                    b = parent[i][b]

            if a != b:
                return parent[0][a]
            else:
                return a

        def distance(self, a, b):
            return self.depth[a] + self.depth[b] - 2 * self.depth[self.lca(a,b)]

        def kth_ancestor(self, a, k):
            parent = self.parent
            if self.depth[a] < k:
                return -1
            for i in range(k.bit_length()):
                if (k >> i) & 1:
                    a = parent[i][a]
            return a

        def __call__(self, a, b):
            depth = self.depth
            parent = self.parent
            data = self.data
            f = self.f
            
            c = self.lca(a, b)
            val = data[0][c]
            for x,d in (a, depth[a] - depth[c]), (b, depth[b] - depth[c]):
                for i in range(d.bit_length()):
                    if (d >> i) & 1:
                        val = f(val, data[i][x])
                        x = parent[i][x]

            return val

    bl = binary_lift(g)

    for u,v in queries:
        if v == 1:
            v = 2
        
        a = bl.kth_ancestor(v-1, bl.distance(0,v-1))

        print(a+1,v+1)

else:
    for u, v in queries:
        print(u+1,v+1)
    

