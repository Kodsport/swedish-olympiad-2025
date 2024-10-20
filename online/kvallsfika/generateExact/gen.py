import random
n = 100000
p = random.randint(1,10000)
k = n
a = [random.randint(1,p) for _ in range(n)]
b = [random.randint(1,k//4) for _ in range(n)]


print(n)
print(p)
print(k)
print(*a)
print(*b)