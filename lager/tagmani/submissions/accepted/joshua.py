#!/usr/bin/python3
# C++ -> Python via chatgpt
# Plus lots of hand-optimization

import sys

sys.setrecursionlimit(100000)

inf = int(1e18)
lomask = (1 << 20) - 1

class CentroidDecomposition:
    def __init__(self, adj):
        self.adj = adj
        self.n = len(adj)
        self.children = [[] for _ in range(self.n)]
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
        if p != -1:
            self.children[p].append(u)
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
    children = decomp.children
    unique_values = [0] * n
    values = [[] for _ in range(n)]
    which_child = [int(2e5) for i in range(n)]
    for i in range(n):
        children[i].sort()
        cc = 2
        for c in children[i]:
            which_child[c] = cc
            cc += 2
    

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

    treesa = [[0 for _ in range(unique_values[i] + 1)] for i in range(n)]
    treesb = [[0 for _ in range(unique_values[i] + 1)] for i in range(n)]

    def add(u: int, t: int, dpv: int):
        c = u
        prevc = -1
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

            ignore_ind = 0 if prevc==-1 else which_child[prevc]
            r = unique_values[c] - hi
            v = dpv+(ignore_ind<<20)
            treea = treesa[c]
            treeb = treesb[c]
            while r < len(treea):
                if (v & lomask) > (treea[r] & lomask):
                    if (treea[r] >> 20) != (treeb[r] >> 20):
                        treeb[r] = treea[r]
                    treea[r] = v
                elif (v & lomask) > (treeb[r] & lomask) and (v >> 20) != (treeb[r] >> 20):
                    treeb[r] = v
                r += (r & -r)

            prevc = c
            c = par[c]
            i += 1

    def query(u: int, t: int) -> int:
        ret = -inf
        c = u
        prevc = -1
        i = 0
        while c != -1:
            ignore_ind = 1 if prevc==-1 else which_child[prevc]
            realt = t + par_dist[u][i]

            # 100 ms faster binary search
            base = 0
            sz = len(values[c])+1
            while sz > 1:
                half = sz//2
                base += (values[c][base+half-1]<realt)*half
                sz -= half

            if base != unique_values[c]:
                treea = treesa[c]
                treeb = treesb[c]
                r = unique_values[c] - base
                while r > 0:
                    if (treea[r] >> 20) != ignore_ind:
                        ret = max(ret, treea[r] & lomask)
                    if (treeb[r] >> 20) != ignore_ind:
                        ret = max(ret, treeb[r] & lomask)
                    r -= (r & -r)

            prevc = c
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
