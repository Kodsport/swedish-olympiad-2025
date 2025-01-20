n, rows, cols = [int(i) for i in input().split()]
grid = [[int(i)-1 for i in input().split()] for rw in range(rows)]

weight = [[0]*cols for r in range(rows)]
ass = [False] * n
for c in range(cols):
    for r in range(rows):
        if not ass[grid[r][c]]:
            weight[r][c] = 1
            ass[grid[r][c]] = True
for r in range(1, rows):
    for c in range(cols):
        weight[r][c] += weight[r-1][c]

L = [0] * n
U = [0] * n
R = [0] * n

top = [{} for i in range(n)]
wup = [{} for i in range(n)]
graph = [set() for i in range(n)]
indeg = [0] * n
for r in range(rows):
    for c in range(cols):
        g = grid[r][c]
        if r > 0:
            up = grid[r-1][c]
            if up != g and g not in graph[up]:
                graph[up].add(g)
                indeg[g] += 1

        if c in top[g].keys():
            continue
        top[g][c] = r
        wup[g][c] = 0 if r == 0 else weight[r-1][c]
        U[g] += wup[g][c]
        

for i in range(n):
    for c in sorted(wup[i].keys())[1:]:
        wup[i][c] += wup[i][c-1]

queue = []
for i in range(n):
    if indeg[i] == 0:
        queue.append(i)

valid = [False] * n
ans = [-1] * n
while queue:
    x = queue.pop()
    valid[x] = True
    for y in graph[x]:
        indeg[y] -= 1
        if indeg[y] == 0:
            queue.append(y)

    l = min(top[x].keys())
    r = max(top[x].keys())
    if top[x][l] != 0:
        par = grid[top[x][l]-1][l]
        L[x] = L[par]
        if min(top[par].keys()) < l:
            L[x] += 1 + wup[par][l-1]

    if top[x][r] > 0:
        par = grid[top[x][r]-1][r]
        R[x] = R[par]
        if max(top[par].keys()) > r:
            #print(x, top[x][r], U[par], wup[par][r])
            R[x] += U[par] - wup[par][r]

    ans[x] = L[x] + U[x] + R[x]
print(*ans)