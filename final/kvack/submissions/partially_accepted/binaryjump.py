#!/usr/bin/env python3
#@EXPECTED_GRADES@ WA WA WA AC WA WA WA
import sys

T = int(input())

out = []

print("?",0)

l = int(input())

out.append(l)

for l in out:

    ## Binärsöka nästa
    lo = l+1
    hi = 10**9
    while lo < hi:
        mid = (lo+hi)//2

        print("?",mid)
        if int(input()) == l:
            lo = mid+1
        else:
            hi = mid


    print("?",lo)
    ans = int(input())
    if ans == l:
        continue
    out.append(ans)

    
print("!",len(out))
sys.stdout.flush()

print(*list(out))
sys.stdout.flush()
