#!/usr/bin/env python3
#@EXPECTED_GRADES@ RTE RTE AC AC TLE TLE TLE
import sys
import random

T = int(input())

out = set()

print("?",0)
l = int(input())
out.add(l)

print("?",10**9)
l = int(input())
out.add(l)

asked = set()

q = 2
while q < 2*len(out)-1:
    x = random.randint(1,1e9-1)
    if x in asked:
        continue
    q += 1
    asked.add(x)

    print("?",x)
    out.add(int(input()))


print("!",len(out))
sys.stdout.flush()

print(*list(out))
sys.stdout.flush()
