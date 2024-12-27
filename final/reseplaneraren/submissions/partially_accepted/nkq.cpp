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

    vvi paths;
    repe(t, trams)
    {
        paths.push_back({});
        path(t.first, t.second, t.first, paths.back());
    }

    mt19937 rng(10);
    shuffle(all(paths), rng);

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        
        bool any = 0;
        repe(p, paths)
        {
            if (find(all(p),a)!=p.end()&&find(all(p),b)!=p.end())
            {
                any = 1;
                break;
            }
        }
        cout << (any ? "Yes" : "No") << "\n";
    }

    return 0;
}
