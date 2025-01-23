#!/usr/bin/env python3

n = int(input())
a = [int(input()) for _ in range(n)]
a.sort()

best = 1e18
for x in range(a[-1]):
    curr = 0
    for i in range(n):
        if a[i] <= x:
            curr += x-a[i]
        else:
            curr += a[-1]-a[i]
    best = min(curr,best)

    

print(best)