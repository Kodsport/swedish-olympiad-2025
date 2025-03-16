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
        prefix = [0]

        for val in include: #Creating for each query and k -> O(qkn)
            if val:
                prefix.append(prefix[-1] + sum(a**t for t in range(currDepth))*x + a**currDepth) #almost O(qnk^2?)
            else:
                prefix.append(prefix[-1] + 1)
        
        l = 0
        r = n
        while l<r:
            m = (l+r)//2
            if prefix[m]== query:
                l = r = m
            elif prefix[m] > query:
                r = m
            else:
                l = m + 1
        
        currRow = l-1 #Zero-index
        if include[currRow]: #If it is an include-line, go deeper
            query -= prefix[currRow]
        else:
            break
    
    print(originalFile[currRow])






