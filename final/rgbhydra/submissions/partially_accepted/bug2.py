#!/usr/bin/env python3

R,G,B,k = map(int,input().split())

if G == B == 0 and k:
    R -= 1
    k -= 1
    G += 1
    B += 1

print(R+k)
