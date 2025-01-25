# @EXPECTED_GRADES@ WA AC WA AC WA WA WA


n, rows, cols = [int(i) for i in input().split()]

mat = [[int(i)-1 for i in input().split()] for r in range(rows)]

pref = [[0]*cols for r in range(rows)]
seen = [False] * n

for r in range(rows):
    for c in range(cols):
        x = mat[r][c]
        if not seen[x]:
            seen[x] = True
            pref[r][c] = 1

for r in range(rows):
    for c in range(1, cols):
        pref[r][c] += pref[r][c-1]

R = [0] * n
L = [0] * n
ans = [-1] * n

for r in range(rows):
    for c in range(cols):
        x = mat[r][c]
        if ans[x] != -1:
            continue

        Rr = r-1
        while Rr < rows - 1 and mat[Rr+1][c] == mat[r][c]:
            Rr += 1
            L[x] += pref[Rr][c]
            R[x] += pref[Rr][c]
        
        if r == 0:
            ans[x] = 0
            continue

        l = mat[r-1][c]
        rr, cr = r, c
        while cr < cols - 1 and mat[rr][cr+1] == mat[rr][cr]:
            cr += 1
        rr -= 1
        pr = mat[rr][cr]

        L[x] += L[l]
        R[x] += R[pr]

        
        L[x] -= 1
        ans[x] = R[x] - L[x]


print(*ans)
