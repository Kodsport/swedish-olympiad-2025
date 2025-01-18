#!/usr/bin/env python3
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

BFS = [(l,r)]
for l,r in BFS:
    print("?",(l+r+1)//2)
    ans = int(input())
    if ans == l or ans == r:
        continue
    found.add(ans)
    BFS.append((l,ans))
    BFS.append((ans,r))

print("?",10**20)
input()

print("!",len(found))
sys.stdout.flush()

print(*list(found))
sys.stdout.flush()
