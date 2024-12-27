#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define __builtin_popcountll popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

const int maxn = int(3e5);
const int maxk = int(5e4);
vvi edges;
vector<p2> trams;


bool path(int s, int t, int p, vi& ret)
{
    if (s == t)
    {
        ret.push_back(s);
        return 1;
    }

    repe(e, edges[s]) if (e != p) if (path(e, t, s, ret))
    {
        ret.push_back(s);
        return 1;
    }
    return 0;
}

signed main()
{
    fast();

    int n, k, q;
    cin >> n >> k >> q;
    edges.resize(n);
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    rep(i, k)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        trams.emplace_back(a, b);
    }

    vector<bitset<maxk>> whichnodes(k);
    rep(i, sz(trams))
    {
        p2 t = trams[i];
        vi the_path;
        path(t.first, t.second, t.first, the_path);
        repe(p, the_path) whichnodes[i][p] = 1;
    }

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;

        bool any = 0;
        rep(i, k)
        {
            any |= whichnodes[i][a] && whichnodes[i][b];
            if (any) break;
        }

        cout << (any ? "Yes" : "No") << "\n";
    }

    return 0;
}
