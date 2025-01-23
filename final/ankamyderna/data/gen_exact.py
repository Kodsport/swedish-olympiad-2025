#!/usr/bin/python3

import sys
import random
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
m = int(cmdlinearg('m'))  
c_is_i = int(cmdlinearg('c_is_i', 0))

mode = cmdlinearg("mode","none")

print(n, m)


if c_is_i:
    colors = [*range(1,m+1)]
else:
    colors = [random.randint(1,n) for _ in range(m)]

ducks = [0]*n
for i,x in enumerate(colors):
    ducks[x-1] += (m-i)**2


if mode == "shift":
    for _ in range(int(cmdlinearg("shift",random.randint(1,10000)))):
        i,j = random.randint(0,n-1),random.randint(0,n-1)
        t = min(int(cmdlinearg("amt",1)),ducks[i])
        if ducks[i]:
            ducks[i] -= t
            ducks[j] += t
elif mode == "remove":
    for _ in range(random.randint(1,min(n,1000))):
        i= random.randint(0,n-1)
        if ducks[i]:
            ducks[i] -= 1
elif mode == "none":
    pass
else:
    assert(0), "There is no such mode that is called: "+mode

print(*ducks)
print(*colors)
