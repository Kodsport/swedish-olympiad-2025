#!/usr/bin/python3

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


prng = random
MAX_G = 10**9

def all_random(n, maxg):
    return [prng.randint(1, maxg) for _ in range(n)]

def arithmetic_sequence(n, diff, reverse=False):
    sequence = [1 + i * diff for i in range(n)]
    assert sequence[-1] <= MAX_G, f"Error: {sequence[-1]} is above the limit {MAX_G}."
    if reverse:
        sequence.reverse()
    return sequence

def exponential_biased(n, maxg, multiplier):
    max_exponent = int(math.log(maxg) / math.log(multiplier))
    exponents = list(range(max_exponent + 1))
    weights = [math.exp(-0.5 * k) for k in exponents]
    chosen_exponents = prng.choices(exponents, weights=weights, k=n)
    result = [multiplier ** exp for exp in chosen_exponents]
    return result

def grouped_large_numbers(n, maxg):
    num_groups = int(math.sqrt(n))
    group_size = n // num_groups
    result = []
    for _ in range(num_groups):
        group = []
        large_num_position = prng.randint(0, group_size - 1)
        for i in range(group_size):
            if i == large_num_position:
                large_num = prng.randint(int(maxg * 0.8), maxg)
                group.append(large_num)
            else:
                small_num = prng.randint(1, max(1, int(math.sqrt(maxg))))
                group.append(small_num)
        result.extend(group)
    remaining = n - len(result)
    for _ in range(remaining):
        result.append(prng.randint(1, int(math.sqrt(maxg))))
    return result

def two_value(n, maxg, ratio=0.5):
    val1 = prng.randint(1, maxg)
    val2 = val1
    while val2 == val1:
        val2 = prng.randint(1, maxg)
    num_val1 = int(n * ratio)
    num_val2 = n - num_val1
    result = [val1] * num_val1 + [val2] * num_val2
    prng.shuffle(result)
    return result

def only_one_large(n, maxg, small_range=9):
    assert maxg >= 10, f"maxg should be at least 10."
    result = [prng.randint(1, small_range) for _ in range(n - 1)]
    large_number = prng.randint(int(maxg * 0.8), maxg)
    insert_position = prng.randint(0, n - 1)
    result.insert(insert_position, large_number)
    return result

def all_same(n, value=1):
    return [value]*n


mode = cmdlinearg("mode", "rand")

maxN = int(cmdlinearg("maxn", 5e5))
n = int(cmdlinearg("n", random.randint(1,maxN)))

if mode == "rand":
    result = all_random(n, int(cmdlinearg("maxg")))
elif mode == "arit":
    result = arithmetic_sequence(n, int(cmdlinearg("diff")), bool(cmdlinearg("rev", 0)))
elif mode == "expo":
    result = exponential_biased(n, int(cmdlinearg("maxg")), int(cmdlinearg("mult")))
elif mode == "large":
    result = only_one_large(n, int(cmdlinearg("maxg")), int(cmdlinearg("small_range", 9)))
elif mode == "group":
    result = grouped_large_numbers(n, int(cmdlinearg("maxg")))
elif mode == "2val":
    result = two_value(n, int(cmdlinearg("maxg")), float(cmdlinearg("ratio", 0.5)))
elif mode == "same":
    result = all_same(n, int(cmdlinearg("value", 1)))
else:
    assert 0, f"Mode {mode = } is not defined."

maxVal = max(result)
E = min(MAX_G - maxVal, int(cmdlinearg("E", 0)))
for i in range(n):
    result[i] += E

print(n,E)
print(*result)
 
