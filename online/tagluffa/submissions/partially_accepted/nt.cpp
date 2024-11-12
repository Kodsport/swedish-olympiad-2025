// O(NT)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const int MAX_T = 250;
const int MAX_N = 100;
vector<vector<p2>> adj;
vector<vector<tuple<int,int,int>>> trains;
int dp[MAX_N][MAX_T+1];
int best(int u, int t)
{
    if (t > MAX_T) return 0;
    int& v = dp[u][t];
    if (v != -1) return v;


    int ret = 0;

    repe(e, adj[u])
    {
        ret = max(ret, best(e.first, t + e.second));
    }

    repe(tr, trains[u])
    {
        int dest, leave, duration;
        tie(dest, leave, duration) = tr;
        if (t<=leave)
        {
            ret = max(ret, 1 + best(dest, leave + duration));
        }
    }

    return v=ret;
}

signed main()
{
    fast();

    memset(dp, -1, sizeof(dp));

    int n, k;
    cin >> n >> k;
    adj.resize(n);
    trains.resize(n);
    rep(i, n - 1)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }
    rep(i, k)
    {
        int a, b, t, d;
        cin >> a >> b >> t >> d;
        a--; b--;
        trains[a].emplace_back(b, t, d);
    }

    rep(i, n)
    {
        cout << best(i, 0) << " ";
    }
    cout << endl;

    return 0;
}
