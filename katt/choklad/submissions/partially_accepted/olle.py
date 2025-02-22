import heapq

n = int(input())

arr = []

pq = []

index = 0

for i in range(n):
    r, c, k = [int(i) for i in input().split()]

    iters = 2 - k%2
    for iter in range(iters):
        if (r//2)*c < r*(c//2):
            r, c = c, r
        heapq.heappush(pq, (-(r//2)*c, (r+1)//2, c, index))
        index += 1
n = index
occs = [[] for i in range(n)]


while pq:
    area, r, c, i = heapq.heappop(pq)

    if area == 0:
        occs[i].append(len(arr))
        arr.append(1)
        continue

    occs[i].append(len(arr))
    arr.append(-area)

    if (r//2)*c < r*(c//2):
        r, c = c, r

    heapq.heappush(pq, (-(r//2)*c, (r+1)//2, c, i))

m = len(arr)

for i in range(m-1):
    assert arr[i] >= arr[i+1]

for i in range(n):
    assert len(occs[i]) > 0


sign = -1
for i in range(1, m):
    arr[i] = arr[i-1] + sign * arr[i]
    sign *= -1

ans = arr[-1]
for i in range(n):
    res = arr[occs[i][0]-1] if occs[i][0] != 0 else 0
    sign = -1
    for j in range(1, len(occs[i])):
        res += sign * (arr[occs[i][j]-1] - arr[occs[i][j-1]])
        sign *= -1
    res += sign * (arr[-1] - arr[occs[i][-1]])
    ans = min(ans, res)
print(ans)