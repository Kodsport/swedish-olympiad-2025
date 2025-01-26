#!/usr/bin/python3
# @EXPECTED_GRADES@ RTE AC RTE RTE RTE RTE RTE


n, rows, cols = [int(i) for i in input().split()]

assert cols == 1
arr = [int(input()) for r in range(rows)]

ans = [0] * n
n = 0
for i in range(1, rows):
    if arr[i] != arr[i-1]:
        n += 1
        ans[arr[i]-1] = n

print(*ans)
