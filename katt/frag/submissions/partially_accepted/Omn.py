

n, m, t = list(map(int, input().split()))

graph = [[] for _ in range(n)]
israt = [False]*n
e = [0]*n
e[0] = 1000000000

children = [[] for _ in range(n)]
parent = [0]*n
visited = [False]*n
rats = []

def build(node, time):
    visited[node] = True
    if israt[node]:
        rats.append((time, node))
        return
    for c, w in graph[node]:
        if visited[c]:
            continue
        if time + w >= t:
            continue
        parent[c] = node
        build(c, time + w)

added = [False]*n
added[0] = True

def add(node):
    if added[node]:
        return
    added[node] = True
    p = parent[node]
    children[p].append(node)
    add(p)

def dp(node = 0):

    if israt[node]:
        return e[node]
    
    sumchildren = 0
    for c in children[node]:
        sumchildren += dp(c)

    return min(e[node], sumchildren)


for i in range(n-1):
    a, b, w = list(map(int, input().split()))

    graph[a].append((b, w))
    graph[b].append((a, w))

for i in range(n-1):
    e[i+1] = int(input())

for i in range(m):
    israt[int(input())] = True


build(0, 0)
rats.sort()

ans = 0
for i  in range(len(rats)):
    time, node = rats[i]

    add(node)
    dpval = dp()

    if i == len(rats)-1:
        ans += (t-time)*dpval
    else:
        ans += (rats[i+1][0]-time)*dpval

print(ans)


    








