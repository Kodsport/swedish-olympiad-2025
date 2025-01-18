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

n = int(cmdlinearg("n"))
#q = int(cmdlinearg("q"))
t = int(cmdlinearg("t"))

if t in [1,2,5,6,7]:
    q = 2*n-1
elif t == 3:
    q = n**2 + n
elif t == 4:
    q = 33*n
    

mode = cmdlinearg("mode", "v1")

print(n, q, t)
pos = set()
if mode == "v1":
    n1 = (n//4)*3
    while len(pos) < n1:
        pos.add(random.randint(0,20000))

    while len(pos) < n:
        pos.add(random.randint(9*10**8,10**9))
elif mode == "v2":
    n1 = (n//4)*1
    while len(pos) < n1:
        pos.add(random.randint(0,20000))

    while len(pos) < n:
        pos.add(random.randint(9*10**8,10**9))
elif mode == "v3":
    t = 1
    pos.add(0)
    pos.add(10**9)
    while t <= 10**9:
        pos.add(t)
        t <<= 1

    n1 = n-1000
    while len(pos) < n1:
        pos.add(random.randint(0,20000))

    while len(pos) < n:
        pos.add(random.randint(9*10**8,10**9))


pos = list(pos)
pos.sort()

print(*pos)