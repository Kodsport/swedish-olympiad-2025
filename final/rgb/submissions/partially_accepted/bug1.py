#!/usr/bin/env python3

R,G,B,k = map(int,input().split())

best = R

print(max(R+k,best))


