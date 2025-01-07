// bellman ford with early break if no more relaxations happen + random order of edges (worst case)
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

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;

    vi result(m);
    vector<vector<p2>> trades(m);
    rep(i, m)
    {
        int what, k;
        cin >> what >> k;
        result[i] = what;
        vector<p2> trade(k);
        rep(j, k) cin >> trade[j].first >> trade[j].second;
        trades[i] = trade;
    }

    const int UNKNOWN = inf;
    vi price(n, UNKNOWN);
    price[0] = 1;

    vi order(m);
    rep(i,m) order[i]=i;
    mt19937 rng(10);
    shuffle(all(order),rng);

    bool changed;
    do
    {
        changed = 0;

        repe(j, order)
        {
            vector<p2>& t = trades[j];
            bool possible = 1;
            repe(u, t) possible &= price[u.second] != UNKNOWN;
            if (!possible) continue;
            int cost = 0;
            repe(u, t) cost += u.first * price[u.second];
            if (cost < price[result[j]])
            {
                price[result[j]] = cost;
                changed = 1;
            }
        }
    } while (changed);
    cout << price.back();

    return 0;
}
