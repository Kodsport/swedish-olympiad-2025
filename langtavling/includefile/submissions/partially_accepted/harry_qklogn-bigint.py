#!/usr/bin/env python3

n,k,q = map(int,input().split())

originalFile = [input() for _ in range(n)]


#Create an array with length n, 
#1 if the row is #include "main.hpp"
#0 if else
include = []
a = 0 #Total number of include-lines
x = 0 #Total number of non-include-lines
for line in originalFile:
    if line == "#include \"main.hpp\"":
        include.append(1)
        a += 1
    else:
        include.append(0)
        x += 1


#Calculate the number of rows that contains in a include-line when there are k-recursions left
apowers = [1] 
for _ in range(k):
    apowers.append(apowers[-1] * a) #apowers[k] = a^k

prefixApowers = [0]
for num in apowers:
    prefixApowers.append(prefixApowers[-1] + num)

lineAmount = [1]
for rec in range(1,k+1):
    #There are rec recursions left.
    lineAmount.append(prefixApowers[rec]*x + apowers[rec]) #lineAmount[rec] = sum(a**t for t in range(rec))*x + a**rec

#Create a prefix sum over number of normal lines and include lines seperately
prefix = [0]
prefixInclude = [0] #Prefix over number of includes
for val in include:
    prefix.append(prefix[-1] + 1 - val)
    prefixInclude.append(prefixInclude[-1] + val)


#Answer queries
for _ in range(q):
    query = int(input())

    for currDepth in range(k,-1,-1):
        #print(currDepth,query)
        #Binary search over which line the current query belongs to
        l = 0
        r = n
        while l<r:
            m = (l+r)//2
            if prefix[m] + prefixInclude[m]*lineAmount[currDepth] == query:
                l = r = m
            elif prefix[m] + prefixInclude[m]*lineAmount[currDepth] > query:
                r = m
            else:
                l = m + 1
        
        currRow = l-1 #Zero-index
        if include[currRow]: #If it is an include-line, go deeper
            query -= prefix[currRow]+prefixInclude[currRow]*lineAmount[currDepth]
        else:
            break
    
    print(originalFile[currRow])





