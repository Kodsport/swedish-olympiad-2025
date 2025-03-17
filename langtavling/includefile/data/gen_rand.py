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

INF = int(1e12)

includes = int(cmdlinearg('inc', random.randint(1,n)))
mode = cmdlinearg('mode', "")





alfa = "qwertyuiopasdfghjklzxcvbnm" + "qwertyuiopasdfghjklzxcvbnm".upper()

file = ["#include \"main.hpp\""]*includes
assert len(file) <= n

while len(file)<n:
    file.append("".join([alfa[random.randint(0,len(alfa)-1)] for _ in range(random.randint(1,3))]))
random.shuffle(file)

queries = []
visited = set()
if includes>1:
    includes_pow = 1
    for _ in range(k+1):
        includes_pow *= includes
        if includes_pow > INF:
            break

    if includes_pow > INF:
        totalLines = INF
    else:
        totalLines = includes**k
        for t in range(k):
            totalLines += (includes**t)*(n-includes)
            if totalLines > INF:
                totalLines = INF
                break
        else:
            totalLines *= includes
            totalLines += n-includes
elif includes == 0:
    totalLines = n
elif includes == 1:
    totalLines = (n-1)*(k+1)+1

for _ in range(q):
    queries.append(random.randint(1,min(totalLines,INF)))

print(n,k,q)
for line in file:
    print(line)

for query in queries:
    print(query)
