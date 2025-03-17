#!/usr/bin/env python3
INF = 1e18
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
for _ in range(k+1):
    apowers.append(apowers[-1] * a) #apowers[k] = a^k
    if apowers[-1] > INF:
        apowers[-1] = float("inf")

prefixApowers = [0]
for num in apowers:
    prefixApowers.append(prefixApowers[-1] + num)

lineAmount = [1]
for rec in range(1,k+2):
    #There are rec recursions left.
    lineAmount.append(prefixApowers[rec]*x + apowers[rec]) #lineAmount[rec] = sum(a**t for t in range(rec))*x + a**rec

#Create a prefix sum over number of normal lines and include lines seperately
prefix = [0]
prefixInclude = [0] #Prefix over number of includes
for val in include:
    prefix.append(prefix[-1] + 1 - val)
    prefixInclude.append(prefixInclude[-1] + val)


if a == 0:
    for _ in range(q):
        print(originalFile[int(input())-1])
    exit()

# Special case if only 1 include
if a == 1:
    ind = include.index(1)
    A = ind*(k+1)
    B = 1
    C = (n-1-ind)*(k+1)
    #print(A,B,C,A+B+C,lineAmount)
    for _ in range(q):
        query = int(input())
        if query == A+B:
            print(originalFile[ind])
        elif query < A+B:
            print(originalFile[(query-1)%ind])
        else:
            print(originalFile[ind+1+(query-1-(A+B))%(n-1-ind)])

    exit()

ind = include.index(1)
A = ind*k # lines before the first include in the compiled file

#Answer queries
for _ in range(q):
    query = int(input())

    # let the file be n = a0,x,a1,x,a2,x,a3,...,ad
    # in each layer of k, calculate the number of lines ad
    
    if query < ind*(k+1)+1:
        print(originalFile[(query-1)%ind])
        continue

    ans = -1
    # Find which k we are in
    currMaxk = k
    if k >= int(1e5):
        query -= (currMaxk-int(1e5))*ind
        currMaxk = int(1e5)

    while currMaxk > 0:
        #print(currMaxk,query)
        if query < ind*(currMaxk+1)+1:
            ans = (query-1)%ind
            break

        hi = currMaxk
        lo = 0
        while lo < hi:
            mid = (lo+hi)//2

            if query - (currMaxk-mid)*ind > lineAmount[mid+1]:
                lo = mid+1
            else:
                hi = mid
        
        query -= (currMaxk-lo)*ind
        if lo == 0:
            break
        #print(query,lo,"before binary search")
        #Binary search on layer lo
        #Binary search over which line the current query belongs to
        l = 0
        r = n
        while l<r:
            m = (l+r)//2
            if prefix[m] + prefixInclude[m]*lineAmount[lo] == query:
                l = r = m
            elif prefix[m] + prefixInclude[m]*lineAmount[lo] > query:
                r = m
            else:
                l = m + 1
        #print(l)
        currRow = l-1 #Zero-index
        #print(include)
        #print(prefix)
        #print(prefixInclude)
        #print(lineAmount)
        if include[currRow] == 0:
            ans = currRow
            break
        else: #If it is an include-line, go deeper
            query -= prefix[currRow]+prefixInclude[currRow]*lineAmount[lo]
            currMaxk = lo-1
                
    #print(query,ans)
    #print(lineAmount,lo)

    if ans != -1:
        print(originalFile[ans])
    else:

        assert(query <= n), f"{query = }"
        print(originalFile[query-1])






