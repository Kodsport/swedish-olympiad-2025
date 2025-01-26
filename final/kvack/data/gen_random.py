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

if t in [1,2,5,6]:
    q = 2*n-1
elif t == 3:
    q = n**2 + n
elif t == 4:
    q = 33*n
    

mode = cmdlinearg("mode", "random")

print(n, q, t)
if mode == "random":
    pos = set()
    while len(pos) < n:
        pos.add(random.randint(0,int(1e9)))
    pos = list(pos)
elif mode == "t2":
    start = int(cmdlinearg("start", random.randint(0,int(1e9)-n+1)))
    pos = [*range(start,start+n)]
elif mode == "manual":
    pos = set(map(int,cmdlinearg("points").split(",")))

    while len(pos) < n:
        pos.add(random.randint(0,int(1e9)))
    pos = list(pos)
else:
    assert(0), "The mode "+mode+" does not exist"

pos.sort()

print(*pos)