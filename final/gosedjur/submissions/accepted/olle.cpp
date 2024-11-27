using namespace std;
#include <bits/stdc++.h>

#define rep(i,a,b) for (int i = a; i < b; i++)
#define pb push_back

typedef long long ll;
typedef vector<ll> vi;

ll n, rows, cols;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> rows >> cols;
    vector<vector<pair<int,int>>> in_animal(n);
    vector<vector<ll>>  animal(rows, vector<ll>(cols)),
                        weight(rows, vector<ll>(cols, 0)),
                        above(rows, vector<ll>(cols));

    vector<ll> L(n, -1), R(n, -1);

    rep(r,0,rows) rep(c,0,cols) cin >> animal[r][c];
    rep(r,0,rows) rep(c,0,cols) animal[r][c]--;
    rep(c,0,cols) rep(r,0,rows) in_animal[animal[r][c]].push_back({r, c});

    rep(i,0,n) {
        auto [r, c] = in_animal[i][0];
        weight[r][c] = 1;
    }

    rep(r,1,rows) rep(c,0,cols) {
        above[r][c] = above[r-1][c] + weight[r-1][c];
    }

    vector<ll> leftpoint(n, 1e18), width(n, 0);
    rep(r,0,rows) rep(c,0,cols) leftpoint[animal[r][c]] = min(leftpoint[animal[r][c]], (ll)c);
    rep(r,0,rows) rep(c,0,cols) width[animal[r][c]] = max(width[animal[r][c]], (ll)c - leftpoint[animal[r][c]] + 1);

    vector<vector<ll>> above_animal(n);
    rep(i,0,n) {
        above_animal[i].assign(width[i], 1e18);
        for (auto [r, c] : in_animal[i]) above_animal[i][c - leftpoint[i]] = min(above_animal[i][c - leftpoint[i]], above[r][c]);
        rep(j,1,(int)above_animal[i].size()) above_animal[i][j] += above_animal[i][j-1];
    }
    
    auto get_above_animal = [&](int i, int l, int r) {
        if (r >= leftpoint[i] + width[i]) r = leftpoint[i] + width[i] - 1;
        if (l < leftpoint[i]) l = leftpoint[i];
        assert(l >= leftpoint[i] && r < leftpoint[i] + width[i]);
        if (r < l) return 0ll;
        ll left = (l == leftpoint[i]) ? 0 : above_animal[i][l - leftpoint[i] - 1];
        return above_animal[i][r - leftpoint[i]] - left;
    };

    vector<int> left_parent(n, -1), right_parent(n, -1);

    rep(c,0,cols) rep(r,1,rows) if (animal[r][c] != animal[r-1][c] && left_parent[animal[r][c]] == -1) 
        left_parent[animal[r][c]] = animal[r-1][c];
    for(int c = cols - 1; c >= 0; c--) rep(r,1,rows) if (animal[r][c] != animal[r-1][c] && right_parent[animal[r][c]] == -1) 
        right_parent[animal[r][c]] = animal[r-1][c];

    vector<set<int>> g(n), rg(n);
    rep(r,1,rows) rep(c,0,cols) {
        int i = animal[r][c], j = animal[r-1][c];
        if (i != j) {
            g[i].insert(j);
            rg[j].insert(i);
        }
    }
    vector<int> order;
    queue<int> q; rep(i,0,n) if (g[i].size() == 0) q.push(i);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        order.push_back(x);
        for (auto y : rg[x]) {
            g[y].erase(x);
            if (g[y].size() == 0) q.push(y);
        }
    }

    vector<ll> ans(n, -1);
    for (auto i : order) {
        if (left_parent[i] == -1) {
            L[i] = 0;
            R[i] = 0;
            ans[i] = 0;
            continue;
        }

        L[i] = L[left_parent[i]];
        if (leftpoint[left_parent[i]] < leftpoint[i]) {
            L[i] += get_above_animal(left_parent[i], leftpoint[left_parent[i]], leftpoint[i]-1);
            L[i]++;
        }
        else {
            L[i] -= get_above_animal(i, leftpoint[i], leftpoint[left_parent[i]] - 1);
        }

        R[i] = R[right_parent[i]];
        int l = min(leftpoint[i], leftpoint[right_parent[i]]);
        R[i] -= get_above_animal(right_parent[i], l, leftpoint[i] + width[i] - 1);
        R[i] += get_above_animal(i, leftpoint[i], leftpoint[i] + width[i] - 1);
        
        ans[i] = L[i] + R[i];
    }

    rep(i,0,n) cout << ans[i] << " ";
    cout << endl;
}