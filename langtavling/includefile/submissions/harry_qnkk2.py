#!/usr/bin/env python3

n,k,q = map(int,input().split())

originalFile = [input() for _ in range(n)]


#Create an array with length n, 
#1 if the row is #include "main.hpp"
#0 if else
include = []
a = 0
x = 0
for line in originalFile:
    if line == "#include \"main.hpp\"":
        include.append(1)
        a += 1
    else:
        include.append(0)
        x += 1


#Answer queries
for _ in range(q):
    query = int(input())

    for currDepth in range(k,-1,-1):
        temp = 0
        for currRow in range(n):
            if include[currRow]:
                temp += sum(a**t for t in range(currDepth))*x + a**currDepth #almost O(qnk^2?)
            else:
                temp += 1
            if temp>=query:
                break

        if include[currRow]: #If it is an include-line, go deeper
            query -= temp - (sum(a**t for t in range(currDepth))*x + a**currDepth)
        else:
            break
    
    print(originalFile[currRow])






