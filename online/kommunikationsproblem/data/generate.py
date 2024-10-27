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
n = int(cmdlinearg("n"))
k = int(cmdlinearg("k"))

print(n, k)
print("".join(random.choice(('0','1')) for i in range(n)))
mode = cmdlinearg("mode")
if mode=="random":
    a,b=random.randint(0,n-1),random.randint(0,n-1)
    if a>b:
        a,b=b,a
    print(a,b)
elif mode=="size1":
    a = random.randint(0,n-1)
    print(a,a)
elif mode=="evenends":
    a = random.randint(0,n-1)
    while a%2==1:
        a = random.randint(0,n-1)
    b = random.randint(0,n-1)
    while b%2==1:
        b = random.randint(0,n-1)
    
    if a>b:
        a,b=b,a
    print(a,b)
elif mode=="lefteven":
    a = random.randint(0,n-1)
    while a%2==1:
        a = random.randint(0,n-1)
    b = random.randint(0,n-1)
    
    if a>b:
        a,b=b,a
    print(a,b)
else:
    assert 0, "No mode provided"