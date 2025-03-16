#!/usr/bin/env python3

n,k,q = map(int,input().split())

assert n == 2

l1 = input()
l2 = input()

if l1 == l2:
    for _ in range(q):
        print(l1)
elif l1 != "#include \"main.hpp\"" and l2 != "#include \"main.hpp\"":
    for _ in range(q):
        if int(input()) == 1:
            print(l1)
        else:
            print(l2)
elif l1 == "#include \"main.hpp\"":
    for _ in range(q):
        if int(input()) == 1:
            print(l1)
        else:
            print(l2)
else: #If l2 == "#include \"main.hpp\""
    for _ in range(q):
        if int(input()) == k+2:
            print(l2)
        else:
            print(l1)
    
