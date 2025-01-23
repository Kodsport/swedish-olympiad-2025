#!/usr/bin/python3

import sys
import random

INF = 10**9

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

def bfs(graph, sand, source = [0]):
    dist = [-1] * n
    for v in source:
        dist[v] = 0
    seen = [0] * n
    q = source
    i = 0
    while i < len(q):
        a = q[i]
        if seen[a] == 0:
            seen[a] = 1
            if sand[a] == 0:
                for b in graph[a]:
                    if dist[b] == -1:
                        dist[b] = dist[a] + 1
                        q.append(b)
        i += 1
    return dist

def random_graph(n, m, branch=INF):
    graph = [[] for _ in range(n)]
    edge_set = set()
    for i in range(1, n):
        p = random.randrange(max(0, i-branch), i)
        graph[i].append(p)
        graph[p].append(i)
        edge_set.add((i, p))
        edge_set.add((p, i))

    for _ in range(m-n+1):
        tries = 0
        fail = 0
        a = random.randrange(1, n)
        b = random.randrange(max(0, a-branch), a)
        while (a, b) in edge_set:
            a = random.randrange(1, n)
            b = random.randrange(max(0, a-branch), a)
            tries += 1
            if tries >= 100:
                fail = 1
                break
        if fail == 0:
            graph[a].append(b)
            graph[b].append(a)
            edge_set.add((a, b))
            edge_set.add((b, a))
    return graph

def print_tc(graph, D, randomize = 1):
    edge_list = []
    for i in range(n):
        for y in graph[i]:
            if y > i:
                if randomize == 1 and random.randint(1,2) == 1:
                    edge_list.append((y, i))
                else:
                    edge_list.append((i, y))

    if randomize == 1:
        random.shuffle(edge_list)
    print(n, len(edge_list))
    print(*D)
    for u, v in edge_list:
        print(u+1,v+1)
    return
    
def line_graph(n):
    graph = [[] for _ in range(n)]
    for i in range(n-1):
        graph[i].append(i+1)
        graph[i+1].append(i)
    return graph

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))
branch = int(cmdlinearg('branch', INF))
mode = cmdlinearg('mode', 'random')
noise = int(cmdlinearg('noise', 0))
n_sand = int(cmdlinearg('sand', 0))

if mode == 'random':
    graph = random_graph(n, m, branch)
    sanded = random.sample(range(n), n_sand)
    sand = [0] * n
    for i in sanded:
        sand[i] = 1
    D = bfs(graph, sand)
    for _ in range(noise):
        i = random.randrange(0, n)
        D[i] = random.randint(0, n)
    D[0] = 0
    print_tc(graph, D)

elif mode == 'line':
    graph = line_graph(n)
    sanded = random.sample(range(n), n_sand)
    sand = [0] * n
    for i in sanded:
        sand[i] = 1
    D = bfs(graph, sand)
    for _ in range(noise):
        i = random.randrange(0, n)
        D[i] = random.randint(0, n)
    D[0] = 0
    print_tc(graph, D, 0)