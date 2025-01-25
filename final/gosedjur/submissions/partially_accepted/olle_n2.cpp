// @EXPECTED_GRADES@ AC TLE TLE  TLE AC TLE TLE

using namespace std;
#include <bits/stdc++.h>

#define rep(i,a,b) for (int i = a; i < b; i++)
#define pb push_back

typedef long long ll;
typedef vector<ll> vi;

ll n, rows, cols;
vector<vector<ll>> animal;
vector<set<int>> g;

bool cycle(int x, vector<int> & v) {
    v[x] = 2;
    for (auto y : g[x]) {
        if (v[y] == 1) continue;
        if (v[y] == 2) return true;
        if (cycle(y, v)) return true;
    }
    v[x] = 1;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> rows >> cols;

    animal.resize(rows);
    rep(r,0,rows) {
        animal[r].resize(cols);
        rep(c,0,cols) cin >> animal[r][c];
        rep(c,0,cols) animal[r][c]--;
    }

    g.resize(n);
    rep(r,1,rows) rep(c,0,cols) {
        int i = animal[r][c], j = animal[r-1][c];
        if (i != j) g[i].insert(j);
    }

    rep(i,0,n) {
        vector<int> v(n, 0);
        if (cycle(i, v)) cout << -1 << " ";
        else {
            int x = -1;
            rep(j,0,n) x += v[j];
            cout << x << " ";
        }
    }
    cout << endl;
}