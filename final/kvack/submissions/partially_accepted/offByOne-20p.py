#!/usr/bin/env python3
#@EXPECTED_GRADES@ AC AC WA WA WA WA WA
import sys
sys.setrecursionlimit(10**4+2)

T = int(input())

print("?",0)

l = int(input())

print("?",10**9)

r = int(input())

found = set()
found.add(l)
found.add(r)



def solve(l,r):
    print("?",(l+r)//2) # Avrundar nedåt
    ans = int(input())

    if ans == l or ans == r:
        return

    found.add(ans)
    
    solve(l,ans)
    solve(ans,r)



solve(l,r)

print("!",len(found))
sys.stdout.flush()

print(*list(found))
sys.stdout.flush()
