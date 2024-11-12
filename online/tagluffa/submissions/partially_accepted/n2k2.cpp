// O(N^2K^2)
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

int dist(int u, int p, int t, int d, vector<vector<p2>>& adj)
{
    if (u==t)
    {
        return d;
    }

    repe(e, adj[u]) if (e.first != p)
    {
        int r = dist(e.first, u, t, d + e.second, adj);
        if (r != -1) return r;
    }
    return -1;
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

    vector<tuple<int, int, int, int>> trains;
    rep(i, k)
    {
        int a, b, t, d;
        cin >> a >> b >> t >> d;
        a--; b--;
        trains.emplace_back(t, a, b, d);
    }
    sort(all(trains));

    rep(i, n)
    {
        vector<tuple<int, int, int>> prev_states;
        int ans = 0;
        prev_states.emplace_back(0, i, 0);

        repe(tr, trains)
        {
            int t, a, b, d;
            tie(t, a, b, d) = tr;

            int best = -inf;
            repe(p, prev_states)
            {
                int ptime, pnode, pdp;
                tie(ptime, pnode, pdp) = p;
                if (dist(pnode,pnode, a, 0, adj) + ptime <= t)
                {
                    best = max(best, 1 + pdp);
                }
            }

            ans = max(ans, best);
            if (best>0)
            {
                prev_states.emplace_back(t + d, b, best);
            }
           
        }

        cout << ans << " ";
    }
    cout << endl;


    return 0;
}
