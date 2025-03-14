#!/usr/bin/python3

import sys
import random

INF = 10**18

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default


random.seed(int(cmdlinearg('seed', sys.argv[-1])))
x = int(cmdlinearg('x', -1))
y = int(cmdlinearg('y', -1))
mode = cmdlinearg("mode", "random")

if mode == "random":
    if x == -1:
        x = random.randint(1, INF)
    if y == -1:
        y = random.randint(1, x)

print(x, y)
    