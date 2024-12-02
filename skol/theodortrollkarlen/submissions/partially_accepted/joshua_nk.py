#!/usr/bin/python3
#@EXPECTED_GRADES@ AC AC AC AC RTE RTE
# Chatgpt c++ -> python
MOD = int(1e9 + 7)

def count_bottomup(n, k, s, a):
    dp = [[0] * (k + 1) for _ in range(n + 1)]
    dp[0][0] = 1

    global_damage = k * a
    for i in range(1, n + 1):
        for j in range(k + 1):
            dp[i][j] += dp[i - 1][j] * global_damage
            dp[i][j] %= MOD

        for j in range(1, k + 1):
            dp[i - 1][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD

        for j in range(1, k + 1):
            dp[i][j] += s * dp[i - 1][j - 1]
            dp[i][j] %= MOD

    ret = 0
    for i in range(k + 1):
        ret += dp[n][i]
    return ret % MOD

def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    n, k, s, a = map(int, data)

    result_a = count_bottomup(n, k, s, a)
    k -= 1
    result_b = count_bottomup(n, k, s, a)

    print((result_a - result_b + MOD) % MOD)

if __name__ == "__main__":
    main()
