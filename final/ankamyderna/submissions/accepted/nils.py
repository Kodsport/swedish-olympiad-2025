#!/usr/bin/python3

n,m = map(int,input().split())
ducks = list(map(int,input().split()))
layer = list(map(int,input().split()))

lo = 0
hi = m+1

while lo < hi-1:
    mid = (lo+hi)//2
    ducks2 = ducks.copy()
    for i in range(mid):
        ducks2[layer[i]-1] -= (mid-i)**2
    if min(ducks2) < 0:
        hi = mid
    else:
        lo = mid
print(lo)
