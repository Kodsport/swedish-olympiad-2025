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

const int maxn = int(5e4);
const int maxk = int(5e4);
vvi edges;
vector<p2> trams;

vector<bitset<maxk>> whichstation(maxn);

int tin[maxn];
int tout[maxn];
int up[maxn][20];
int timer = 0;

void dfs(int u, int p)
{
    tin[u] = timer++;
    up[u][0] = p;

    repp(d, 1, 20) up[u][d] = up[up[u][d-1]][d - 1];

    repe(e, edges[u]) if (e!=p) dfs(e, u);

    tout[u] = timer++;
}

bool isancestor(int a, int b)
{
    return tin[a] <= tin[b] && tin[b] <= tout[a];
}

int lca(int a, int b)
{
    if (isancestor(a, b)) return a;
    if (isancestor(b, a)) return b;
    for (int d = 19; d >= 0; d--)
    {
        if (!isancestor(up[a][d], b))
        {
            a = up[a][d];
        }
    }
    return up[a][0];
}

vvi activate;
vvi deactivate;
void dfs2(int u, int p)
{
    repe(e, edges[u]) if (e != p)
    {
        dfs2(e, u);
        whichstation[u] |= whichstation[e];
    }

    repe(v, activate[u]) whichstation[u][v] = 1;


    repe(v, deactivate[u]) whichstation[u][v] = 0;
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
    dfs(0, 0);
    activate.resize(n);
    deactivate.resize(n);



    rep(i, sz(trams))
    {
        p2 t = trams[i];
        activate[t.first].push_back(i);
        activate[t.second].push_back(i);
        int l = lca(t.first, t.second);
        if (l!=0) deactivate[up[l][0]].push_back(i);
    }
    dfs2(0, 0);

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;

        cout << ((whichstation[a] & whichstation[b]).count() > 0 ? "Yes" : "No") << "\n";
    }

    return 0;
}
