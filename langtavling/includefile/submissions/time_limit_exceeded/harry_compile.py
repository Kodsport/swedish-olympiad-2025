#!/usr/bin/env python3

n,k,q = map(int,input().split())

originalFile = [input() for _ in range(n)]

prevFile = originalFile[:]

for _ in range(k): #O(size of compiled file)
    newFile = []
    for line in prevFile:
        if line == "#include \"main.hpp\"":
            newFile += originalFile
        else:
            newFile.append(line)
    prevFile,newFile = newFile,prevFile


for _ in range(q):
    print(prevFile[int(input())-1])
