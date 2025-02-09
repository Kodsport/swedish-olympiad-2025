#!/usr/bin/python3
# C++ -> Python via chatgpt
# Plus lots of hand-optimization

import sys

sys.setrecursionlimit(100000)

inf = int(1e18)

class CentroidDecomposition:
    def __init__(self, adj):
        self.adj = adj
        self.n = len(adj)
        self.par = [-1] * self.n
        self.size = [0] * self.n
        self.par_dist = [[] for _ in range(self.n)]
        self.init_centroid(0, -1)

    def init_centroid(self, u: int, p: int):
        bfs = [(u,-1)]
        for v, par in bfs:
            self.size[v] = 1
            for e, _ in self.adj[v]:
                if e!=par:
                    bfs.append((e, v))
        for v, par in reversed(bfs):
            for e, _ in self.adj[v]:
                if e != par:
                    self.size[v] += self.size[e]

        cp = u
        compsz = self.size[u]
        while True:
            any = 0
            for v, _ in self.adj[u]:
                if v != cp and self.size[v] > compsz // 2:
                    any = 1
                    cp = u
                    u = v
                    break
            if not any:
                break
        
        bfs = [(u, 0, par)]
        for v, dist, par in bfs:
            self.par_dist[v].append(dist)
            for e, d in self.adj[v]:
                if e != par:
                    bfs.append((e, dist+d, v))

        self.par[u] = p
        i = 0
        while i < len(self.adj[u]):
            e, _ = self.adj[u][i]
            for j in range(len(self.adj[e])):
                if self.adj[e][j][0]==u:
                    del self.adj[e][j]
                    break
            self.init_centroid(e, u)
            i += 1



def main():
    n,k = [int(i) for i in input().split()]

    adj = [[] for _ in range(n)]
    for _ in range(n - 1):
        a, b, c = [int(i) for i in input().split()]
        a-=1
        b-=1
        adj[a].append((b, c))
        adj[b].append((a, c))
    trains = []
    for _ in range(k):
        a, b, t, d = [int(i) for i in input().split()]
        a-=1
        b-=1
        trains.append((t + d, a, b, d))
    trains.sort(reverse=True)

    decomp = CentroidDecomposition(adj)
    par = decomp.par
    par_dist = decomp.par_dist
    for i in range(n):
        par_dist[i].reverse()
    unique_values = [0] * n
    values = [[] for _ in range(n)]
    

    def add_nodes(u: int, t: int):
        c = u
        i = 0
        while c != -1:
            unique_values[c] += 1
            values[c].append(t - par_dist[u][i])
            c = par[c]
            i += 1

    for i in range(k):
        t, a, b, d = trains[i]
        add_nodes(a, t-d)
    add_nodes(0, inf)

    for i in range(n):
        values[i].sort()

    trees = [[0 for _ in range(unique_values[i] + 1)] for i in range(n)]

    def add(u: int, t: int, dpv: int):
        c = u
        i = 0
        while c != -1:
            realt = t - par_dist[u][i]
            lo = -1
            hi = len(values[c])
            while lo+1<hi:
                mid = (lo+hi)//2
                if values[c][mid] < realt:
                    lo = mid
                else:
                    hi=mid

            r = unique_values[c] - hi
            tree = trees[c]
            while r < len(tree):
                tree[r] = max(tree[r], dpv)
                r += (r & -r)

            c = par[c]
            i += 1

    def query(u: int, t: int) -> int:
        ret = -inf
        c = u
        i = 0
        while c != -1:
            realt = t + par_dist[u][i]

            # 100 ms faster binary search
            base = 0
            sz = len(values[c])+1
            while sz > 1:
                half = sz//2
                base += (values[c][base+half-1]<realt)*half
                sz -= half

            if base != unique_values[c]:
                tree = trees[c]
                r = unique_values[c] - base
                while r > 0:
                    ret = max(ret, tree[r])
                    r -= (r & -r)

            c = par[c]
            i += 1
        return ret

    add(0, inf, 0)

    for i in range(len(trains)):
        t, a, b, d = trains[i]
        best = query(b, t)
        if best >= 0:
            add(a, t - d, best + 1)

    output = []
    for i in range(n):
        output.append(str(query(i, 0)))
    print(" ".join(output))


if __name__ == "__main__":
    main()
