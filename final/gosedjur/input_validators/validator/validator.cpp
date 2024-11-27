#include "validator.h"

#include <bits/stdc++.h>
using namespace std;

#define fo(i, n) for(ll i=0;i<((ll)n);i++)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void run() {
    int n = Int(1, Arg("maxn"));
    Space();
    int rows = Int(1, Arg("maxr"));
    Space();
    int cols = Int(1, Arg("maxc"));
    Endl();

    vector<vector<int>> mat(rows, vector<int>(cols));
    vector<int> occ(n, 0);
    rep(r,0,rows) rep(c,0,cols) {
        mat[r][c] = Int(1, n);
        if (c < cols - 1) Space();
        else Endl();
        occ[mat[r][c]-1]++;
    }
    Eof();

    rep(i,0,n) assert(occ[i]);

    auto nei = [&](int r, int c) {
        vector<pair<int,int>> ret;

        vector<pair<int,int>> cand = {
            {r+1, c}, {r, c+1}, {r-1, c}, {r, c-1}
        };

        for (auto [R, C] : cand) {
            if (R < 0 || R >= rows || C < 0 || C >= cols) continue;
            if (mat[r][c] == mat[R][C]) ret.push_back({R, C});
        }

        return ret;
    };

    int dc = 0;
    vector<vector<int>> v(rows, vector<int>(cols, 0));

    rep(r,0,rows) rep(c,0,cols) {
        if (v[r][c]) continue;
        v[r][c] = 1;
        dc++;
        queue<pair<int,int>> q;
        q.push({r, c});
        while (!q.empty()) {
            auto [R, C] = q.front();
            for (auto [dr, dc] : nei(R, C)) {
                if (v[dr][dc]) continue;
                v[dr][dc] = true;
                q.push({dr, dc});
            }
        }
    }

    assert(dc == n);
}