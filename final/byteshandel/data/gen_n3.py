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

MAX_COEF = 100
MAX_K = 100000  # If you need a sum of LHS terms constraint

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
mode = cmdlinearg('mode')

# We always have N=3 => items: 0, 1, 2.
# We'll store equations as (res_item, [(coef, lhs_item), ...]).
equations = []



if mode == "random":
    num_equations = 50000
    for _ in range(num_equations):
        res = randint(0, 2)
        k = randint(1, 2)
        terms = [i for i in range(3)]
        terms.pop(res)
        if k == 1:
            terms.pop(randint(0, 1))
        lhs_list = []
        for i in terms:
            coef = randint(1, MAX_COEF)
            lhs_list.append((coef, i))
        equations.append((res, lhs_list))

if mode == "skip_1":
    eq1 = (1, [(50, 0)])   
    eq2 = (2, [(70, 0)])       
    eq3 = (2, [(1, 0), (2, 1)]) 
    equations = [eq1, eq2, eq3]

if mode == "force_1":
    eq1 = (1, [(1, 0)])
    eq2 = (2, [(5, 0)])
    eq3 = (2, [(2, 1)])
    equations = [eq1, eq2, eq3]

if mode == "two_paths_small_1":
    eq1 = (1, [(1, 0)])
    eq2 = (2, [(100, 0), (1, 1)])
    eq3 = (2, [(1, 0), (99, 1)])
    equations = [eq1, eq2, eq3]

if mode == "two_paths_big_1":
    eq1 = (1, [(100, 0)])
    eq2 = (2, [(1, 0), (2, 1)])  
    eq3 = (2, [(100, 0), (1, 1)])
    equations = [eq1, eq2, eq3]

if mode == "mixed_random":
    num_equations = 50000
    mid = randint(40, 60)
    for _ in range(num_equations):
        pattern = random.choice(["0->1", "1->2", "0+1->2"])

        if pattern == "0->1":
            coef = randint(1, mid)
            eq = (1, [(coef, 0)])
            equations.append(eq)

        elif pattern == "1->2":
            coef = randint(mid, 100)
            eq = (2, [(coef, 1)])
            equations.append(eq)

        else:
            coef0 = randint(mid, 100)
            coef1 = randint(mid, 100)
            eq = (2, [(coef0, 0), (coef1, 1)])
            equations.append(eq)


n = 3
random.shuffle(equations)
m = len(equations)
print(f"{n} {m}")
for (res, lhs_list) in equations:
    print(f"{res} {len(lhs_list)}")
    for (coef, item) in lhs_list:
        print(f"{coef} {item}")
