#!/usr/bin/python3

n, m, t = map(int, input().split())

graph = [[] for _ in range(n)]

for _ in range(n-1):
    x,y,ti = map(int,input().split())
    