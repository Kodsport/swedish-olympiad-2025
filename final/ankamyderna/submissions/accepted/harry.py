#!/usr/bin/env python3

n,m = map(int,input().split())

a = [*map(int,input().split())]
c = [*map(lambda x: int(x)-1,input().split())]

def solve(H):
    b = a[:]
    for i in range(H):
        if b[c[i]] >= (H-i)**2:
            b[c[i]] -= (H-i)**2
        else:
            return 0
    return 1

l = 0
r = m

while l < r:
    mid = (l+r+1)//2

    if solve(mid):
        l = mid
    else:
        r = mid-1

print(l)