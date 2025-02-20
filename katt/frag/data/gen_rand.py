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
m = int(cmdlinearg('k'))
t = int(cmdlinearg('t'))
maxs = int(cmdlinearg("maxs"))
dmult = int(cmdlinearg("dmult", 3))


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

totdist = 0
print(n, k)
for i in range(n-1):
    while True:
        a,b=randint(0,n-1),randint(0,n-1)
        if a==b:continue
        if uf.find(a)==uf.find(b):continue
        uf.union(a,b)
        s = randint(1, maxs)
        totdist += s
        print(a+1,b+1, s)
        break

seen_times = set()
for i in range(k):
    while 1:
        time = randint(0, t)
        if late_trains:
            time += totdist + 20
        if time in seen_times:
            continue
        seen_times.add(time)
        a = randint(1,n)
        b = randint(1,n)
        while b==a:
            b = randint(1,n)
        print(a, b, time, randint(1, maxs*dmult))
        break