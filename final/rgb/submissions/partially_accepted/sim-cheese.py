#!/usr/bin/env python3

R,G,B,k = map(int,input().split())



if max(R,G,B,k) <= 10:
    best = R

    if G == B == 0 and k:
        R -= 1
        k -= 1
        G += 1
        B += 1
    print(max(R+k,best))

else:
    best = R

    if G == B == 0:
        R -= 1
        k -= 1
        G += 1
        B += 1
    print(max(R+k,best,1)) # The answer is not always > 0


