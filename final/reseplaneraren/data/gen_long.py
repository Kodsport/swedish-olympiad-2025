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

g4 = int(cmdlinearg('g4',0))

def shuffle_nodes(edgelist, star1, star2):
    nodes = list(set(node for edge in edgelist for node in edge))

    # Generate a mapping from old labels to new labels
    label_mapping = {old_label: new_label for old_label, new_label in zip(nodes, random.sample(nodes, len(nodes)))}

    # Apply the label mapping to the edges
    shuffled_graph = [(label_mapping[u], label_mapping[v]) for u, v in edgelist]
    star1 = [label_mapping[u] for u in star1]
    star2 = [label_mapping[u] for u in star2]

    return (shuffled_graph, star1,star2)

nn = n
print(n,k,q)
n-=1
cnt = 0
root = 1
tail = -1
i = 1
edgelist = []
# Long line graph 33%
while cnt < n//3:
    edgelist.append((i+1,i))
    tail = i+1
    i+=1
    cnt+=1

star1 = []
# Star graph at bottom 33%
while cnt<n//3*2:
    edgelist.append((i+1,tail))
    star1.append(i+1)
    i+=1
    cnt+=1

# Extra random edges into bottom star 10%
for j in range(n//10):
    u = random.choice(star1)
    if randint(1,100)==1:
        edgelist.append((u, i+1))
    else:
        edgelist.append((i+1, u))
    star1.append(i+1)
    i+=1
    cnt+=1

star2 = []
# Star graph at top 23%
while cnt < n:
    edgelist.append((root, i+1))
    star2.append(i+1)
    i+=1
    cnt+=1

edgelist,star1,star2=shuffle_nodes(edgelist,star1,star2)

random.shuffle(edgelist)

g = [[] for _ in range(nn)]

for i in edgelist:
    print(i[0],i[1])
    g[i[0]-1].append(i[1]-1)
    g[i[1]-1].append(i[0]-1)

for i in range(k):
    print(random.choice(star1), random.choice(star2))


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

    for _ in range(q):
        b = random.randint(2,nn)
        a = bl.kth_ancestor(b-1, randint(1,bl.distance(0,b-1)))

        print(a+1,b)

else:
    for i in range(q):
        print(random.choice(star1), random.choice(star2))

