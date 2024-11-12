#!/usr/bin/python3
# C++ -> Python via chatgpt

import sys
import bisect

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

    def calc_size(self, u: int, p: int):
        self.size[u] = 1
        for v, _ in self.adj[u]:
            if v != p:
                self.calc_size(v, u)
                self.size[u] += self.size[v]

    def find_centroid(self, u: int, p: int, n: int) -> int:
        for v, _ in self.adj[u]:
            if v != p and self.size[v] > n // 2:
                return self.find_centroid(v, u, n)
        return u

    def calc_dist(self, u: int, p: int, d: int):
        self.par_dist[u].append(d)
        for v, dist in self.adj[u]:
            if v != p:
                self.calc_dist(v, u, d + dist)

    def init_centroid(self, u: int, p: int):
        self.calc_size(u, -1)
        u = self.find_centroid(u, -1, self.size[u])
        self.calc_dist(u, -1, 0)
        self.par[u] = p
        if p != -1:
            self.children[p].append(u)
        i = 0
        while i < len(self.adj[u]):
            v, _ = self.adj[u][i]
            self.adj[v] = [(x, y) for x, y in self.adj[v] if x != u]
            self.init_centroid(v, u)
            i += 1


class FenwickTree:
    def __init__(self, n: int):
        self.n = n
        self.tree = [(0, 0) for _ in range(n + 1)]

    def f(self, a, b):
        max1, max2 = 0, 0
        for val in [a[0], a[1], b[0], b[1]]:
            if (val & lomask) > (max1 & lomask):
                if (max1 >> 20) != (max2 >> 20):
                    max2 = max1
                max1 = val
            elif (val & lomask) > (max2 & lomask) and (val >> 20) != (max2 >> 20):
                max2 = val
        return max1, max2

    def update(self, r: int, v):
        r = self.n - 1 - r
        r += 1
        while r < len(self.tree):
            self.tree[r] = self.f(self.tree[r], v)
            r += (r & -r)

    def query(self, l: int):
        ret = (0, 0)
        r = self.n - 1 - l
        r += 1
        while r > 0:
            ret = self.f(self.tree[r], ret)
            r -= (r & -r)
        return ret


def main():
    input = sys.stdin.read
    data = input().split()
    idx = 0
    n = int(data[idx])
    k = int(data[idx + 1])
    idx += 2
    adj = [[] for _ in range(n)]
    for _ in range(n - 1):
        a, b, c = int(data[idx]) - 1, int(data[idx + 1]) - 1, int(data[idx + 2])
        adj[a].append((b, c))
        adj[b].append((a, c))
        idx += 3
    trains = []
    for _ in range(k):
        a, b, t, d = int(data[idx]) - 1, int(data[idx + 1]) - 1, int(data[idx + 2]), int(data[idx + 3])
        trains.append((t + d, a, b, d))
        idx += 4
    trains.sort(reverse=True)

    decomp = CentroidDecomposition(adj)
    par = decomp.par
    par_dist = decomp.par_dist
    for i in range(n):
        par_dist[i].reverse()
    children = decomp.children
    unique_values = [0] * n
    values = [[] for _ in range(n)]
    child_index = [[] for _ in range(n)]

    for i in range(n):
        children[i].append(-1)
        for c in children[i]:
            child_index[i].append((c, len(child_index[i]) + 1))
        child_index[i].sort()

    def add_nodes(u: int, t: int):
        c = u
        i = 0
        while c != -1:
            unique_values[c] += 1
            values[c].append(t - par_dist[u][i])
            c = par[c]
            i += 1

    for t, a, b, d in trains:
        add_nodes(a, t - d)
    add_nodes(0, inf)

    for i in range(n):
        values[i].sort()

    trees = [FenwickTree(unique_values[i]) for i in range(n)]

    def add(u: int, t: int, dpv: int):
        c = u
        prevc = -1
        i = 0
        while c != -1:
            realt = t - par_dist[u][i]
            ind = bisect.bisect_left(values[c], realt)
            ignore_ind = bisect.bisect_left(child_index[c], (prevc, inf))
            trees[c].update(ind, (dpv + (ignore_ind << 20), 0))
            prevc = c
            c = par[c]
            i += 1

    def query(u: int, t: int) -> int:
        ret = -inf
        c = u
        prevc = -1
        i = 0
        while c != -1:
            ignore_ind = inf if prevc == -1 else bisect.bisect_left(child_index[c], (prevc, inf))
            realt = t + par_dist[u][i]
            ind = bisect.bisect_left(values[c], realt)
            if ind != unique_values[c]:
                res = trees[c].query(ind)
                if (res[0] >> 20) != ignore_ind:
                    ret = max(ret, res[0] & lomask)
                if (res[1] >> 20) != ignore_ind:
                    ret = max(ret, res[1] & lomask)
            prevc = c
            c = par[c]
            i += 1
        return ret

    add(0, inf, 0)

    for t, a, b, d in trains:
        best = query(b, t)
        if best >= 0:
            add(a, t - d, best + 1)

    output = []
    for i in range(n):
        output.append(str(query(i, 0)))
    print(" ".join(output))


if __name__ == "__main__":
    main()
