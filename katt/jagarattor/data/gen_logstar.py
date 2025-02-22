#!/usr/bin/python3

import sys
import random
import math
from random import randint as rand
from common import connect, add_rats

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
q = int(cmdlinearg('q'))
decay = float(cmdlinearg('decay'))

def generate_graph(n):
    edges = set()
    prev_layer = [0]
    i = 1
    rem = n-1
    while 1:
        layer_size = int(rem*decay)
        rem -= layer_size
        if layer_size == 0:
            break
            
        next_layer = []
        for j in range(layer_size):
            edges.add((i, random.choice(prev_layer)))
            next_layer.append(i)
            i+=1

        prev_layer = next_layer

    edges = connect(edges, n)
    return add_rats(edges, n)

edges = generate_graph(n)

print(n, len(edges), q)
for e in edges:
    print(*(i+1 for i in e[:2]))


def unique_choice(choices):
    while True:
        pos = random.randint(1,n)
        if pos not in choices:
            return pos


for i in range(q):
    s = unique_choice([])
    r = unique_choice([s])
    t = unique_choice([s,r])
    
    print(s,r,t)
