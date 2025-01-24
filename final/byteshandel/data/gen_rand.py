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

MIN_COEF = 1
MAX_COEF = 20
MAX_TERMS = 4

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

chain_len = int(cmdlinearg('chain_len'))
sumk = int(cmdlinearg('sumk'))
num_chains = int(cmdlinearg('num_chains'))
mode = cmdlinearg('mode', "normal")

if mode == "single_lhs":
    MIN_COEF = 2
    MAX_COEF = 50

# all nodes except 0 and n-1 are part of the chains, they are the beginning and ending of all chains
# a chain starts at 0, goes through chain_len - 2 nodes, and ends at n-1
# this generator makes num_chains chains and then uses the rest of the sumk to add random edges
# we need small coefficients to make sure the number does not exceed 1e9
# also dont want too many coefficients on the left side, that would give us too few edges

n = (chain_len - 2) * num_chains + 2
equations = []  # tuple of (res, [(coef, item), ...])
all_chains = []

chain_ends = []
for c1 in range(num_chains):
    chain = [0]
    for c2 in range(chain_len - 2):
        chain.append(1 + c1 * (chain_len - 2) + c2)
    chain_ends.append(chain[-1])
    all_chains.append(chain[1:])
    
    for c2 in range(1, chain_len - 1):
        lhs_pairs = []
        lhs_pairs.append((randint(MIN_COEF, MAX_COEF), chain[c2 - 1]))
        sumk -= 1
        if mode == "normal" or mode == "acyclic":
            for c3 in range(c2 - 1):
                if randint(0, 1):
                    lhs_pairs.append((randint(MIN_COEF, MAX_COEF), chain[c3]))
                    sumk -= 1
        eq = (chain[c2], lhs_pairs)
        equations.append(eq)

if mode == "normal" or mode == "acyclic":
    lhs_pairs = []
    for item in chain_ends:
        lhs_pairs.append((randint(MIN_COEF, MAX_COEF), item))
        sumk -= 1
    eq = (n - 1, lhs_pairs)
    equations.append(eq)

if mode == "single_lhs":
    for item in chain_ends:
        lhs_pairs = []
        lhs_pairs.append((randint(MIN_COEF, MAX_COEF), item))
        sumk -= 1
        eq = (n - 1, lhs_pairs)
        equations.append(eq)

assert sumk >= 0

if mode == "normal" or mode == "acyclic":
    while sumk > 0:
        if sumk == 1:
            terms = 1
        else:
            terms = randint(2, min(MAX_TERMS, sumk))
        res = randint(1, n - 2)
        lhs_pairs = []
        used_items = [res]
        while terms > 0:
            item = randint(1, n - 2)
            if item in used_items:
                continue
            used_items.append(item)
            terms -= 1
            lhs_pairs.append((randint(MAX_COEF * 2, MAX_COEF * 3), item))
            sumk -= 1
            if sumk < 0:
                break

        if mode == "acyclic":
            biggest = max(used_items)
            if biggest != res:
                for i in range(len(lhs_pairs)):
                    if lhs_pairs[i][1] == biggest:
                        lhs_pairs[i] = (lhs_pairs[i][0], res)
                res = biggest

        eq = (res, lhs_pairs)
        equations.append(eq)

if mode == "single_lhs":
     while sumk > 0:
        chain_pos = randint(0, 2)
        chain_res = randint(0, num_chains - 1)
        chain_lhs = randint(0, num_chains - 1)
        while chain_res == chain_lhs:
            chain_lhs = randint(0, num_chains - 1)
        
        res = all_chains[chain_res][chain_pos]
        item = all_chains[chain_lhs][chain_pos]
        coef = randint(2, 5)
        eq = (res, [(coef, item)])
        sumk -= 1
        equations.append(eq)

assert sumk >= 0

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
for (res, lhs_pairs) in equations:
    print(f"{res} {len(lhs_pairs)}")
    for (coef, it) in lhs_pairs:
        print(f"{coef} {it}")
