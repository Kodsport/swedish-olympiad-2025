#!/usr/bin/python3

import sys
import random
import math

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

maxN = int(cmdlinearg("maxN", 1000000))
n = int(cmdlinearg('n', random.randint(1,maxN)))
maxk = int(cmdlinearg('maxk', 100000))
k = int(cmdlinearg('k', random.randint(1,maxk)))
q = int(cmdlinearg('q', random.randint(100,1000)))

length = int(cmdlinearg("length", 3))

INF = int(1e12)

includes = int(cmdlinearg('inc', random.randint(1,n)))
mode = cmdlinearg('mode', "none")


alfa = "qwertyuiopasdfghjklzxcvbnm" + "qwertyuiopasdfghjklzxcvbnm".upper()

file = ["#include \"main.hpp\""]*includes

while len(file)<n:
    file.append("".join([alfa[random.randint(0,len(alfa)-1)] for _ in range(random.randint(random.randint(1,length//2),length))]))
file.sort()

if mode == "rev":
    file.reverse()
else:
    assert(mode == "none"), f"Mode {mode=} not defined"

queries = []
visited = set()

if includes**k > INF:
    totalLines = INF
else:
    totalLines = sum(includes**t for t in range(k))*(n-includes) + includes**k
    totalLines *= includes
    totalLines += n-includes

for _ in range(q):
    queries.append(random.randint(1,min(totalLines,INF)))

print(n,k,q)
for line in file:
    print(line)

for query in queries:
    print(query)
