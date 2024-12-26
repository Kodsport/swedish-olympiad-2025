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
n = int(cmdlinearg('n'))
k = int(cmdlinearg('k'))
print(n, k)
mode = cmdlinearg('mode')
alpha = [chr(ord('a')+i) for i in range(k)]
if mode == "random":
    print("".join(random.choice(alpha) for i in range(n)))
elif mode == "rainbow":
    s = []
    while len(s) < n:
        s += alpha
    while len(s) > n:
        del s[-1]
    print("".join(s))
elif mode == "unbalanced":
    s = []
    s += alpha
    c = random.choice(alpha)
    for i in range(n-k):
        s.append(c)
    random.shuffle(s)
    print("".join(s))
elif len(mode) == 1:
    print(mode*n)
else:
    assert 0, f"Unknown mode {mode}"