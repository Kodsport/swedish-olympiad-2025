#!/usr/bin/python3

import sys
import random
import math

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

maxN = int(cmdlinearg("maxN", 1000000))
n = int(cmdlinearg('n', random.randint(1,maxN)))
maxk = int(cmdlinearg('maxk', 100000))
k = int(cmdlinearg('k', random.randint(1,maxk)))
q = int(cmdlinearg('q', random.randint(100,1000)))

length = int(cmdlinearg("length", 3))

INF = int(1e12)

includes = int(cmdlinearg('inc', random.randint(1,n)))
mode = cmdlinearg('mode', "none")


alfa = "qwertyuiopasdfghjklzxcvbnm" + "qwertyuiopasdfghjklzxcvbnm".upper()

file = ["#include \"main.hpp\""]*includes

while len(file)<n:
    file.append("".join([alfa[random.randint(0,len(alfa)-1)] for _ in range(random.randint(random.randint(1,length//2),length))]))
random.shuffle(file)


queries = []
visited = set()

if includes**k > INF:
    totalLines = INF
else:
    totalLines = sum(includes**t for t in range(k))*(n-includes) + includes**k
    totalLines *= includes
    totalLines += n-includes



INF2 = int(1e18)

#Create an array with length n, 
#1 if the row is #include "main.hpp"
#0 if else
include = []
a = 0 #Total number of include-lines
x = 0 #Total number of non-include-lines
for line in file:
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
    if apowers[-1] > INF2:
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
        queries.append(random.randint(1,min(totalLines,INF)))

elif mode == "none": # there exist at least 1 includefile
    ind = include.index(1)
    A = ind*(k+1)

    scale = int(cmdlinearg("scale", 5))
    curr = A + 1
    for _ in range(q):
        queries.append(curr)
        curr += lineAmount[random.randint(1,min(scale,k+1))] + random.randint(0,4)
        if curr > INF or curr > totalLines or curr != curr:
            curr = min(A+lineAmount[2] + random.randint(0,n), totalLines, INF)
            scale = max(2,scale-1)

elif mode == "dec":
    scale = int(cmdlinearg("scale", 5))
    curr = min(totalLines,INF)
    for _ in range(q):
        queries.append(curr)
        curr -= lineAmount[random.randint(1,min(scale,k+1))] - random.randint(0,4)
        if curr < 1:
            curr = min(totalLines,INF) - random.randint(0,n)
            scale = max(2,scale-1)
else:
    assert(mode == "none"), f"Mode {mode=} not defined"

print(n,k,q)
for line in file:
    print(line)

for query in queries:
    print(query)
