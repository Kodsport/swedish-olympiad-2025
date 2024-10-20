p = 32
a = [*map(int,input().split())]
print(*[x if x <= p else p for x in a])