#!/usr/bin/python3

from itertools import combinations
import sys
input = sys.stdin.readline


def cut_tree(graph, rootset = 0):
    n = len(graph)
    new_graph = [[] for _ in range(n)]
 
    P = [-1] * n
    depth = [-1] * n
    biconnect = [None] * n
    root = rootset
 
    preorder = []
    stack = [root]
    while stack:
        node = stack.pop()
        if depth[node] >= 0:
            continue
        depth[node] = len(preorder)
        preorder.append(node)
        for nei in graph[node]:
            if depth[nei] == -1:
                P[nei] = node
                stack.append(nei)
    preorder.pop(0)
 
    for node in reversed(preorder):
        depth[node] = min(depth[nei] for nei in graph[node]) 
        if depth[P[node]] == depth[node]:
            bicon = biconnect[node] = [P[node], node]
            new_graph.append(bicon)
   
    for node in preorder:
        if biconnect[node] is None:
            bicon = biconnect[node] = biconnect[P[node]]
            bicon.append(node)
    
    for bicon_ind in range(n, len(new_graph)):
        for node in new_graph[bicon_ind]:
            new_graph[node].append(bicon_ind)
 
    return new_graph

class RangeQuery:
    def __init__(self, data, func=min):
        self.func = func
        self._data = _data = [list(data)]
        i, n = 1, len(_data[0])
        while 2 * i <= n:
            prev = _data[-1]
            _data.append([func(prev[j], prev[j + i]) for j in range(n - 2 * i + 1)])
            i <<= 1

    def query(self, begin, end):
        depth = (end - begin).bit_length() - 1
        return self.func(self._data[depth][begin], self._data[depth][end - (1 << depth)])


class LCA:
    def __init__(self, root, graph):
        self.time = [-1] * len(graph)
        self.path = [-1] * len(graph)
        P = [-1] * len(graph)
        t = -1
        dfs = [root]
        while dfs:
            node = dfs.pop()
            self.path[t] = P[node]
            self.time[node] = t = t + 1
            for nei in graph[node]:
                if self.time[nei] == -1:
                    P[nei] = node
                    dfs.append(nei)
        self.rmq = RangeQuery(self.time[node] for node in self.path)

    def __call__(self, a, b):
        if a == b:
            return a
        a = self.time[a]
        b = self.time[b]
        if a > b:
            a, b = b, a
        return self.path[self.rmq.query(a, b)]
    
def find_SCC(graph):
    SCC, S, P = [], [], []
    depth = [0] * len(graph)
 
    stack = list(range(len(graph)))
    while stack:
        node = stack.pop()
        if node < 0:
            d = depth[~node] - 1
            if P[-1] > d:
                SCC.append(S[d:])
                del S[d:], P[-1]
                for node in SCC[-1]:
                    depth[node] = -1
        elif depth[node] > 0:
            while P[-1] > depth[node]:
                P.pop()
        elif depth[node] == 0:
            S.append(node)
            P.append(len(S))
            depth[node] = len(S)
            stack.append(~node)
            stack += graph[node]
    return SCC[::-1]


r,c,q = map(int,input().split())
grid = [[*input()] for _ in range(r)]

graph = [[] for _ in range(r*c)]

def c2i(i,j):
    return i*c + j
def i2c(x):
    return (x//c,x%c)

notEmpty = 0

for i in range(r):
    for j in range(c):
        for di,dj in [(1,0),(0,1)]:
            if 0 <= i+di < r and 0 <= j+dj < c:
                if grid[i][j] == grid[i+di][j+dj] == ".":
                    notEmpty = c2i(i,j)
                    graph[c2i(i,j)].append(c2i(i+di,j+dj))
                    graph[c2i(di+i,dj+j)].append(c2i(i,j))


#Divide up the graph into components before running cut_tree 
newGraph = [[] for _ in range(len(graph))]


visited = [0]*len(graph)
for i in range(len(graph)):
    if visited[i]:
        continue
    visited[i] = 1
    BFS = [i]
    for curr in BFS:
        for nei in graph[curr]:
            if visited[nei]:
                continue
            visited[nei] = 1
            BFS.append(nei)
    
    ind2temp = {x:i for i,x in enumerate(BFS)}
    #print(ind2temp)
    
    #print(BFS,graph)
    tempGraph = [[ind2temp[node] for node in graph[x]] for x in BFS]

    tempNewGraph = cut_tree(tempGraph)
    #print(tempGraph,"tempgraph")
    #print(tempNewGraph)

    for ii in range(len(tempGraph),len(tempNewGraph)):
        BFS.append(len(newGraph))
        newGraph.append([])
    
    for ii,adj in enumerate(tempNewGraph):
        newGraph[BFS[ii]] += [BFS[x] for x in adj]
    #print(newGraph,"newgraph")


depths = [-1]*len(newGraph)
treeInd = [-1]*len(newGraph)
treeLCA = []


ind2Tree = {} #for each index in the cut_tree, map it to which tree it is in and which node in that itree
tree2ind = {}

t = 0
for start in range(len(newGraph)):
    if depths[start] != -1:
        continue

    depths[start] = 0
    BFS = [start]
    treeInd[start] = t


    # give each tree an index and run LCA on it.
    for curr in BFS:
        for nei in newGraph[curr]:
            if depths[nei] == -1:
                depths[nei] = depths[curr] + 1
                BFS.append(nei)
                treeInd[start] = t
    
    node2newInd = {}
    for i,x in enumerate(BFS):
        node2newInd[x] = i
        tree2ind[(t,i)] = x
        ind2Tree[x] = (t,i)
    
    tempTree = [[node2newInd[node] for node in newGraph[x]] for x in BFS]
    #print(tempTree)
    treeLCA.append(LCA(0,tempTree))
    
    #print(t,start,depths)
    t += 1


# Precompute all nodes and edges
# each node has a state (x,y,s)
# 0 - above, 1 - right, 2- under, 3- left
mainGraph = [[] for _ in range(r*c*4)]
for i in range(r):
    for j in range(c):
        if grid[i][j] == "#":
            continue

        for (d1,di1,dj1),(d2,di2,dj2) in combinations([(0,-1,0),(1,0,1),(2,1,0),(3,0,-1)],2):

            #If box is in (i,j): Check if you can go from above the box to the right of the box 
            if 0 <= i+di1 < r and 0 <= i+di2 < r and 0 <= j+dj1 < c and 0 <= j+dj2 < c:
                if grid[i+di1][j+dj1] == "#" or grid[i+di2][j+dj2] == "#":
                    continue
                ind1 = c2i(i+di1,j+dj1)
                ind2 = c2i(i+di2,j+dj2)
                indb = c2i(i,j)

                _,i1 = ind2Tree[ind1]
                _,i2 = ind2Tree[ind2]
                t,ib = ind2Tree[indb]

                connected = 1
                if treeLCA[t](i1,ib) == ib or treeLCA[t](i2,ib) == ib:
                    if depths[tree2ind[(t,treeLCA[t](i1,i2))]] <= depths[indb]:
                        connected = 0
                
                if connected:
                    mainGraph[c2i(i,j)*4 + d1].append(c2i(i,j)*4 + d2)
                    mainGraph[c2i(i,j)*4 + d2].append(c2i(i,j)*4 + d1)
        

        # Check if it can be pushed in all 4 directions
        for d,di,dj in [(0,-1,0),(1,0,1),(2,1,0),(3,0,-1)]:
            if 0 <= i+di < r and 0 <= i-di < r and 0 <= j+dj < c and 0 <= j-dj < c:
                if grid[i+di][j+dj] == "#" or grid[i-di][j-dj] == "#":
                    continue
                mainGraph[c2i(i,j)*4 + d].append(c2i(i-di,j-dj)*4 + d)

# Create the same graph, but with the edges reversed
revGraph = [[] for _ in range(len(mainGraph))]
for i in range(len(mainGraph)):
    for u in mainGraph[i]:
        revGraph[u].append(i)


# Precompute connectivity
reachable = [1<<i for i in range(len(mainGraph))] # Using integers as bitsets here
for SCC in find_SCC(mainGraph)[::-1]:
    temp = 0
    for x in SCC:
        temp |= reachable[x]
    for x in SCC:
        reachable[x] |= temp
        for nei in revGraph[x]:
            reachable[nei] |= reachable[x]
    



for _ in range(q):
    # we have to check if the starting position can reach any of the four sides of the box. 
    # from that position, is it possible to push the box in the goal
    xs,ys,xb,yb,xt,yt = map(lambda x: int(x)-1,input().split())

    inds = c2i(xs,ys)
    indb = c2i(xb,yb)
    indt = c2i(xt,yt)

    ts,ii = ind2Tree[inds]
    tb,ib = ind2Tree[indb]
    tt,it = ind2Tree[indt]


    found = 0
    if tt == ts == tb:
        for d,di,dj in [(0,-1,0),(1,0,1),(2,1,0),(3,0,-1)]:
            if 0 <= xb+di < r  and 0 <= yb+dj < c and not found:
                if grid[xb+di][yb+dj] == "#":
                    continue

                ind1 = c2i(xb+di,yb+dj)
                _,i1 = ind2Tree[ind1]

                connected = 1
                if treeLCA[t](i1,ib) == ib or treeLCA[t](ii,ib) == ib:
                    if depths[tree2ind[(t,treeLCA[t](i1,ii))]] <= depths[indb]:
                        connected = 0
                
                if connected:
                    currNode = c2i(xb,yb)*4 + d

                    for goal in range(c2i(xt,yt)*4,c2i(xt,yt)*4+4):
                        if reachable[currNode] & (1<<goal):
                            
                            print("Ja")
                            found = 1
                            break

    if not found:
        print("Nej")


"""
10 10 1
#.......#.
.....#..#.
..###.....
#..#...##.
..........
........#.
..##...##.
..##...#..
......#..#
......#...
1 8 4 2 10 4



"""