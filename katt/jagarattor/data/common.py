import random
# Stolen from https://github.com/cheran-senthil/PyRival/blob/master/pyrival/data_structures/DisjointSetUnion.py
class UF:
    def __init__(self, n):
        self.parent = list(range(n))

    def find(self, a):
        acopy = a
        while a != self.parent[a]:
            a = self.parent[a]
        while acopy != a:
            self.parent[acopy], acopy = a, self.parent[acopy]
        return a

    def union(self, a, b):
        self.parent[self.find(b)] = self.find(a)

def connect(edges, n):
    uf = UF(n)
    numcomps = n
    for a,b in edges:
        if uf.find(a)!=uf.find(b):
            uf.union(a,b)
            numcomps-=1

    while numcomps>1:
        a,b=random.sample(range(0,n),2)
        if (a,b) in edges or (b,a) in edges:
            continue
        if uf.find(a)==uf.find(b):
            continue
        uf.union(a,b)
        edges.add((a,b))
        numcomps-=1
    return edges

def add_rats(edges, n):
    adj = [[] for i in range(n)] 

    for u,v in edges:
        adj[u].append(v)
        adj[v].append(u)

    ret = []
    for u,v in edges:
        a = random.choice(adj[v])
        b = random.choice(adj[u])
        
        ret.append((u,v,a,b))
    return ret