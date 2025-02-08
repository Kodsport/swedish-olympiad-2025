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
q = int(cmdlinearg('q'))
maxv = int(cmdlinearg('maxv'))

mode = cmdlinearg('mode','same')


if mode == "same":
    arr = [random.randint(0,maxv)]*n
elif mode == "diff":
    arr = [i%(maxv+1) for i in range(n)]
else:
    assert(0), f"Mode {mode} is not implemented."

print(n,q)

print(*arr)

phaseSize = int(cmdlinearg('phaseSize',q))


queriesUsed = 0
while queriesUsed < q:
    
    ind = randint(1,max(1,n-min(q-queriesUsed, phaseSize)))
    qs = [*range(ind,ind+min(q-queriesUsed, phaseSize))]
    random.shuffle(qs)

    c = (arr[ind-1]+1)%(maxv+1) #pick a color different from arr[ind] 

    for qind in qs:
        if qind > n:
            continue

        print(qind,c)
        arr[qind-1] = c
        queriesUsed += 1


    
