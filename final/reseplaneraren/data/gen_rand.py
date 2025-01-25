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

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
k = int(cmdlinearg('k'))
q = int(cmdlinearg('q'))

mode = cmdlinearg('mode','none')

# Stolen from https://github.com/cheran-senthil/PyRival/blob/master/pyrival/data_structures/DisjointSetUnion.py
class UF:
    def __init__(self, n):
        self.parent = list(range(n))

    def find(self, a):
        acopy = a
        while a != self.parent[a]:
            a = self.parent[a]
        while acopy != a:
            self.parent[acopy], acopy = a, self.parent[acopy]
        return a

    def union(self, a, b):
        self.parent[self.find(b)] = self.find(a)

uf = UF(n)

g = [[] for _ in range(n)]

print(n, k, q)
for i in range(n-1):
    while True:
        a,b=randint(0,n-1),randint(0,n-1)
        if a==b:continue
        if uf.find(a)==uf.find(b):continue
        uf.union(a,b)
        print(a+1,b+1)
        
        g[a].append(b)
        g[b].append(a)
        break

trams = []
queries = []

for i in range(k+q):
    while True:
        a,b=randint(0,n-1),randint(0,n-1)
        if a==b:continue
        
        if i < k:
            trams.append((a+1,b+1))
        else:
            queries.append((a+1,b+1))
        break

for a,b in trams:
    print(a,b)

if mode == "none":
    for a,b in queries:
        print(a,b)
elif mode == "g4":
    
    """
    BFS = [0]
    chi = [[] for _ in range(n)]
    par = [0]
    dis = [-1]*n
    dis[0] = 0
    for cur in BFS:
        for nei in g[cur]:
            if dis[nei] != -1:
                continue
            dis[nei] = 1 + dis[cur]
            BFS.append(nei)
            chi[cur].append(nei)
    """
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

    for _ in range(q):
        b = random.randint(2,n)
        a = bl.kth_ancestor(b-1, bl.distance(0,b-1))

        print(a+1,b)
else:
    assert(0), "The mode "+mode+" does not exist."