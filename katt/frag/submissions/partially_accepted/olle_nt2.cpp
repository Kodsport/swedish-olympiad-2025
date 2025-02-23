using namespace std;
#include <bits/stdc++.h>

#define rep(i,a,b) for(int i = a; i < b; i++)
typedef long long ll;

ll n, m, t;

vector<vector<pair<ll,ll>>> g; // {i, weight}
vector<ll> e, rat;

vector<vector<ll>> dp;

void dfs(int x, int p) {
    for (auto [y, w] : g[x]) if (y != p) dfs(y, x);

    dp[x][0] = 0;
    rep(T,1,t+1) {
        if (rat[x]) {
            dp[x][T] = T * e[x];
        }
        else {
            dp[x][T] = 1e18;
            
            rep(T2,0,T+1) { // how much to pay in this node?
                ll res = T2 * e[x];
                for (auto [y, w] : g[x]) if (y != p) {
                    ll time = T - T2 - w;
                    if (time >= 0) res += dp[y][time];
                }
                dp[x][T] = min(dp[x][T], res);
            }
        }
    }
}

int main() {
    cin >> n >> m >> t;
    g.resize(n);
    e.assign(n, 0);
    rat.assign(n, 0);
    dp.resize(n);
    rep(i,0,n) dp[i].assign(t+1, 0);
    rep(i,0,n-1) {
        ll a, b, w;
        cin >> a >> b >> w;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    rep(i,1,n) cin >> e[i];
    rep(i,0,m) {
        int r; cin >> r; rat[r] = 1;
    } 

    dfs(0, -1);

    ll ans = 0;
    for (auto [x, w] : g[0]) {
        ans += dp[x][t-w];
    }

    cout << ans << endl;
}