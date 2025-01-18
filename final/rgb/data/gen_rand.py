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

R = int(cmdlinearg("R",randint(1, 1e18)))
G = int(cmdlinearg("G",randint(1, 1e18)))
B = int(cmdlinearg("B",randint(1, 1e18)))
k = int(cmdlinearg("k",randint(1, 1e18)))

print(R,G,B,k)
