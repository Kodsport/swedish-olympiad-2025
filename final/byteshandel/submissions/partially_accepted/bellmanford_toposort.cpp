// bellman ford with early break if no more relaxations happen. we do relaxations in approximate topological order
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

void toposort(int u, vi& vis, vi& order, vvi& adj)
{
    if (vis[u]) return;
    vis[u] = 1;
    repe(e, adj[u]) toposort(e, vis, order, adj);
    order.push_back(u);
}

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;

    vvi adj(n);
    vector<vector<vector<p2>>> mytrades(n);
    rep(i, m)
    {
        int what, k;
        cin >> what >> k;
        vector<p2> trade(k);
        rep(j, k) cin >> trade[j].first >> trade[j].second;
        mytrades[what].push_back(trade);
        repe(u, trade) adj[what].push_back(u.second);
    }

    vi vis(n);
    vi order;
    vi dfsorder(n);
    rep(i, n) dfsorder[i] = i;
    mt19937 rng(10);
    shuffle(all(dfsorder), rng);
    repe(u, dfsorder) toposort(u, vis, order, adj);

    const int UNKNOWN = inf;
    vi price(n, UNKNOWN);
    price[0] = 1;

    bool changed;
    do
    {
        changed = 0;

        repe(j, order)
        {
            repe(t, mytrades[j])
            {
                bool possible = 1;
                repe(u, t) possible &= price[u.second] != UNKNOWN;
                if (!possible) continue;
                int cost = 0;
                repe(u, t) cost += u.first * price[u.second];
                if (cost < price[j])
                {
                    price[j] = cost;
                    changed = 1;
                }
            }
        }
    } while (changed);
    cout << price.back();

    return 0;
}
