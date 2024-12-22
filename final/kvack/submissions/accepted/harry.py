#!/usr/bin/env python3

n = 100

for _ in range(n):
    s = input()
    if len(s) > 3:
        print("a")
    else:
        print(s + "a")

