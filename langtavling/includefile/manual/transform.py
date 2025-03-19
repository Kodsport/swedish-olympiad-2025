#!/usr/bin/python3
n,k,q = map(int,input().split())
lines = [input() for _ in range(n)]

INF = int(1e12)

print(n,k,q)
print("\n".join(lines))
for _ in range(q):
    print((int(input())-1)%INF + 1)
