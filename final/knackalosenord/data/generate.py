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
shuffle = int(cmdlinearg('shuffle', 0))

print(n, k)
mode = cmdlinearg('mode')
alpha = [chr(ord('a')+i) for i in range(k)]
if mode == "random":
    print("".join(random.choice(alpha) for i in range(n)))
elif mode == "rainbow": # equal distribution over the letters
    s = []
    while len(s) < n:
        s += alpha
    while len(s) > n:
        del s[-1]
    if shuffle:
        random.shuffle(s)
    print("".join(s))
elif mode == "unbalanced":
    s = []
    s += alpha
    c = random.choice(alpha)
    for i in range(n-k):
        s.append(c)
    if shuffle:
        random.shuffle(s)
    print("".join(s))
elif len(mode) == 1:
    s = [mode] * n
    for i in range(5):
        s[random.randint(0, n-1)] = random.choice(alpha)
    print("".join(s))
else:
    assert 0, f"Unknown mode {mode}"
