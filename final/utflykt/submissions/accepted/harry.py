#!/usr/bin/env python3

n = int(input())
a = [int(input()) for _ in range(n)]
a.sort()

best = curr = a[-1]*n - sum(a)
for i in range(n):
    curr -= a[-1]-a[i]
    if i:
        curr += i*abs(a[i]-a[i-1])
    best = min(best,curr)

print(best)