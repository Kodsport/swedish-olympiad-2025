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
focal = int(cmdlinearg("focal"))
samerat = int(cmdlinearg("samerat", 0))
samegoal = int(cmdlinearg("samerat", 0))

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

    for i in range(20):
        a,b=random.sample(range(0,n),2)
        if (a,b) in edges or (b,a) in edges:
            continue
        edges.add((a,b))
    
    edges = connect(edges, n)
    return add_rats(edges, n)

edges = generate_graph(n)

print(n, len(edges), q)
for e in edges:
    print(*(i+1 for i in e))


def unique_choice(choices):
    while True:
        pos = random.randint(2,n)
        if pos not in choices:
            return pos


if samerat:
    if focal == 0:
        s = 1
        r = unique_choice([s])
    elif focal == 1:
        r = 1
        s = unique_choice([r])
    else:
        s = unique_choice([])
        r = unique_choice([s])
    for i in range(q):
        t = unique_choice([s,r])
        query = [s,r,t]
        if focal==2 and rand(0,100) > 0:
            query[focal] = 1
        print(*query)

elif samegoal:
    if focal == 2:
        t = 1
    else:
        t = unique_choice([])

    for i in range(q):
        s = unique_choice([t])
        r = unique_choice([s,t])

        query = [s,r,t]
        if focal==2 and rand(0,100) > 0:
            query[focal] = 1
        print(*query)

else:
    for i in range(q):
        s = unique_choice([])
        r = unique_choice([s])
        t = unique_choice([s,r])
        query = [s,r,t]
        if rand(0,100) > 0:
            query[focal] = 1
        print(*query)
