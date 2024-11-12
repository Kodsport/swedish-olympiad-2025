// O(NlogN+NKlogN+K^2logN)
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

const int maxn = int(2e5);
int timer = 0;
int tin[maxn];
int tout[maxn];
int depth[maxn];
int up[19][maxn];

void dfs(int u, int p, int d, vector<vector<p2>>& adj)
{
    depth[u] = d;
    tin[u] = timer++;
    up[0][u] = p;
    repp(d, 1, 19)
    {
        up[d][u] = up[d - 1][up[d - 1][u]];
    }


    repe(e, adj[u]) if (e.first != p) dfs(e.first, u, d + e.second, adj);

    tout[u] = timer++;
}

int isancestor(int a, int b)
{
    return tin[a] <= tin[b] && tin[b] <= tout[a];
}

int lca(int a, int b)
{
    if (isancestor(a, b)) return a;
    if (isancestor(b, a)) return b;

    for (int d = 18; d >= 0; d--)
    {
        if (!isancestor(up[d][a],b))
        {
            a = up[d][a];
        }
    }

    return up[0][a];
}

int dist(int a, int b)
{
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

signed main()
{
    fast();


    int n, k;
    cin >> n >> k;
    vector<vector<p2>> adj(n);
    rep(i, n - 1)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }
    dfs(0, 0, 0, adj);

    vector<tuple<int, int, int, int>> trains;
    rep(i, k)
    {
        int a, b, t, d;
        cin >> a >> b >> t >> d;
        a--; b--;
        trains.emplace_back(t+d, a, b, d);
    }
    sort(all(trains));
    reverse(all(trains));

    vector<tuple<int, int, int>> prev_states;
    prev_states.emplace_back(inf, 0, 0);

    repe(tr, trains)
    {
        int t, a, b, d;
        tie(t, a, b, d) = tr;

        int best = -inf;
        repe(p, prev_states)
        {
            int ptime, pnode, pdp;
            tie(ptime, pnode, pdp) = p;
            if (dist(pnode,b) + t <= ptime)
            {
                best = max(best, 1 + pdp);
            }
        }

        if (best > 0)
        {
            prev_states.emplace_back(t - d, a, best);
        }

    }

    rep(i, n)
    {
        int ans = 0;

        repe(p, prev_states)
        {
            int ptime, pnode, pdp;
            tie(ptime, pnode, pdp) = p;
            if (dist(pnode,i) <= ptime)
            {
                ans = max(ans, pdp);
            }
        }
        cout << ans << " ";
    }
    cout << endl;

    return 0;
}
