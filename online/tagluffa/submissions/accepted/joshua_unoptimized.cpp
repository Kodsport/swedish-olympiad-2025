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
        if (!isancestor(up[d][a], b))
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

struct centroid
{
    vvi adj, children;
    vi par, size;
    centroid(vvi adj) : adj(adj), children(sz(adj)), par(sz(adj)), size(sz(adj))
    {
        init_centroid(0, -1);
    }

    void calc_sz(int u, int p)
    {
        size[u] = 1;
        repe(e, adj[u]) if (e != p) calc_sz(e, u), size[u] += size[e];
    }

    int find_centroid(int u, int p, int n)
    {
        repe(e, adj[u]) if (e != p && size[e] > n / 2) return find_centroid(e, u, n);
        return u;
    }

    void init_centroid(int u, int p)
    {
        calc_sz(u, -1);
        u = find_centroid(u, -1, size[u]);
        par[u] = p;
        if (p != -1) children[p].push_back(u);
        repe(e, adj[u])
        {
            adj[e].erase(find(all(adj[e]), u));
            init_centroid(e, u);
        }
    }
};

const int lomask = (1 << 20) - 1;

struct maxtree {
    typedef p2 T;
    static constexpr T unit = p2(0, 0);
    T f(T a, T b)
    {
        int max1 = 0, max2 = 0;

        for (int val : {a.first, a.second, b.first, b.second}) {
            if ((val&lomask) > (max1&lomask)) {
                if ((max1>>20)!=(max2>>20))
                {
                    max2 = max1; // update second largest
                }          
                
                max1 = val;  // update largest
            }
            else if ((val&lomask) > (max2&lomask) && (val>>20) != (max2>>20)) {
                max2 = val;  // update second largest if it's not the largest
            }
        }

        return p2(max1, max2);
    } // (any associative fn)
    vector<T> s; int n;
    maxtree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) { // query [b, e)
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};


signed main()
{
    fast();
    
    int n, k;
    cin >> n >> k;
    vector<vector<p2>> adj(n);
    vvi normal_adj(n);
    rep(i, n - 1)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
        normal_adj[a].push_back(b);
        normal_adj[b].push_back(a);
    }
    dfs(0, 0, 0, adj);

    vector<tuple<int, int, int, int>> trains;
    rep(i, k)
    {
        int a, b, t, d;
        cin >> a >> b >> t >> d;
        a--; b--;
        trains.emplace_back(t + d, a, b, d);
    }
    sort(all(trains));
    reverse(all(trains));

    centroid decomp(normal_adj);
    vi par = decomp.par;
    vvi children = decomp.children;
    vi unique_values(n);
    vvi values(n);
    vector<map<int, int>> child_index(n);
    rep(i, n)
    {
        children[i].push_back(-1);

        repe(c, children[i])
        {
            child_index[i][c] = sz(child_index[i])+1;
        }
    }

    auto add_nodes = [&](int u, int t)
        {
            int c = u;
            int prevc = -1;
            while (c != -1)
            {
                unique_values[c]++;
                values[c].push_back(t - dist(u, c));
                prevc = c;
                c = par[c];
            }
        };

    repe(tr, trains)
    {
        int t, a, b, d;
        tie(t, a, b, d) = tr;

        add_nodes(a, t-d);
    }
    add_nodes(0, inf);
    rep(i, n) sort(all(values[i]));

    vector<maxtree> trees(n);
    rep(i, n)
    {
        trees[i] = maxtree(unique_values[i]);
    }

    auto add = [&](int u, int t, int dpv)
        {
            int c = u;
            int prevc = -1;
            while (c != -1)
            {
                int realt = t - dist(u, c);
                int ind = lower_bound(all(values[c]), realt) - values[c].begin();
                trees[c].update(ind, p2(dpv + (child_index[c][prevc] << 20),0));
                prevc = c;
                c = par[c];
            }
        };

    int lb_calls = 0;
    auto query = [&](int u, int t)
        {
            int ret = -inf;
            int c = u;
            int prevc = -1;
            while (c != -1)
            {
                int ignoreind = prevc == -1 ? inf : child_index[c][prevc];
                int realt = t + dist(u, c);
                int ind = lower_bound(all(values[c]), realt) - values[c].begin();

                if (ind!= unique_values[c])
                {
                    p2 res = trees[c].query(ind, unique_values[c]);
                    if ((res.first >> 20) != ignoreind)
                    {
                        ret = max(ret, res.first & lomask);
                    }
                    if ((res.second >> 20) != ignoreind)
                    {
                        ret = max(ret, res.second & lomask);
                    }
                }
                
                prevc = c;
                c = par[c];
            }
            return ret;
        };

    add(0, inf, 0);

    repe(tr, trains)
    {
        int t, a, b, d;
        tie(t, a, b, d) = tr;

        int best = query(b, t);

        if (best >= 0)
        {
            add(a, t - d, best+1);
        }
    }

    rep(i, n)
    {
        cout << query(i,0) << " ";
    }
    cout << endl;

    return 0;
}
