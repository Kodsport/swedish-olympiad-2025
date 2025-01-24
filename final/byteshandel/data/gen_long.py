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

equations = []
prod = 1
for i in range(n-1):
    coef = 1
    if prod * 10 < 10**9 and randint(0, 30) == 0:
        coef = randint(2, 10)
        prod *= coef
    equations.append((i+1, [(coef, i)]))
    m -= 1

while m:
    i = 1
    while m and i < n :
        equations.append((i-1, [(coef, i)]))
        i += 1        
        m -= 1


permute = list(range(1, n - 1))
random.shuffle(permute)

def apply_permutation(item):
    if item == 0 or item == n - 1:
        return item
    else:
        return permute[item - 1]

new_equations = []
for (res, lhs_list) in equations:
    new_res = apply_permutation(res)
    new_lhs = []
    for (coef, it) in lhs_list:
        new_it = apply_permutation(it)
        new_lhs.append((coef, new_it))
    new_equations.append((new_res, new_lhs))

equations = new_equations

random.shuffle(equations)
m = len(equations)
print(f"{n} {m}")
for (res, lhs_list) in equations:
    print(f"{res} {len(lhs_list)}")
    for (coef, item) in lhs_list:
        print(f"{coef} {item}")
