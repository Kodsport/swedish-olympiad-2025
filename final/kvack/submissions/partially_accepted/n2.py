#!/usr/bin/env python3
#@EXPECTED_GRADES@ AC WA WA WA AC WA WA
import sys

T = int(input())

out = []

print("?",0)
l = int(input())
out.append(l)

print("?",10**9)
l = int(input())
out.append(l)

asked = set()

found = 1
while found:
    found = 0
    for i in range(len(out)-1):

        print("?", (out[i]+out[i+1]+1)//2)
        ans = int(input())
        if ans == out[i] or ans == out[i+1]:
            continue
        out = out[:i+1] + [ans] + out[i+1:]
        found = 1
        break

print("!",len(out))
sys.stdout.flush()

print(*list(out))
sys.stdout.flush()
