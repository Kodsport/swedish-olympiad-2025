#!/usr/bin/env python3
n = int(input())
t = sorted([int(input()) for _ in range(n)])
tot = sum([t[-1]-t[i] for i in range(n)])
print(min([tot-(i+1)*(t[-1]-t[i]) for i in range(n)]))
