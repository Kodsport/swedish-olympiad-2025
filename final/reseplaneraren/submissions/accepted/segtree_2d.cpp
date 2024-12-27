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

int tin[maxn];
int tout[maxn];
int depth[maxn];
int up[maxn][20];
int timer = 0;

void dfs(int u, int p)
{
    depth[u] = depth[p] + 1;
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

int maxup[maxn];
vector<vector<p2>> activate;
vector<vector<p2>> deactivate;
set<p2> dfs2(int u, int p)
{
    set<p2> ret;
    repe(e, edges[u]) if (e != p)
    {
        set<p2> o = dfs2(e, u);
        if (sz(ret) < sz(o)) swap(ret, o);
        repe(v, o) ret.insert(v);
    }
    repe(a, activate[u]) ret.insert(a);

    if (sz(ret)) maxup[u] = begin(ret)->first;
    else maxup[u] = -1;

    repe(v, deactivate[u]) ret.erase(v);
    return ret;
}

struct Segtree
{
    int n;
    vi tree;
    vi realindex;

    Segtree() {}

    Segtree(vi nums)
    {

        map<int, int> occs;
        rep(i, nums.size()) occs[nums[i]]++;
        n = occs.size();
        tree = vi(n * 4);
        int i = 0;
        repe(num, occs)
        {
            realindex.push_back(num.first);
            update(i, num.second);
            i++;
        }
    }

    void update(int x, int l, int r, int i, int v)
    {
        if (l > i || r < i) return;
        if (l == r) tree[x] += v;
        else
        {
            int mid = (l + r) / 2;
            update(x * 2, l, mid, i, v);
            update(x * 2 + 1, mid + 1, r, i, v);
            tree[x] = tree[x * 2] + tree[x * 2 + 1];
        }
    }
    void update(int i, int v) { update(1, 0, n - 1, i, v); }

    int query(int x, int l, int r, int ql, int qr)
    {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return tree[x];
        int mid = (l + r) / 2;
        return query(x * 2, l, mid, ql, qr) + query(x * 2 + 1, mid + 1, r, ql, qr);
    }

    int query(int ql, int qr)
    {
        ql = lower_bound(all(realindex), ql) - realindex.begin();
        qr = upper_bound(all(realindex), qr) - realindex.begin() - 1;
        return query(1, 0, n - 1, ql, qr);
    }
};

struct Tree2D
{
    int n;
    vector<Segtree> trees;
    vvi points;
    vi realindex;

    Tree2D(vector<p2> points)
    {
        map<int, vi> rows;
        repe(p, points)
        {
            rows[p.first].push_back(p.second);
        }

        repe(num, rows)
        {
            realindex.push_back(num.first);
        }

        n = rows.size();
        trees = vector<Segtree>(n * 4);
        this->points = vvi(n * 4);

        vvi values;
        repe(row, rows) values.push_back(row.second);
        build(1, 0, n - 1, values);
    }

    void build(int x, int l, int r, vvi& values)
    {
        if (l == r)
        {
            points[x] = values[l];
            trees[x] = Segtree(values[l]);
        }
        else
        {
            int mid = (l + r) / 2;
            build(x * 2, l, mid, values);
            build(x * 2 + 1, mid + 1, r, values);

            repe(p, points[x * 2]) points[x].push_back(p);
            repe(p, points[x * 2 + 1]) points[x].push_back(p);
            trees[x] = Segtree(points[x]);
        }
    }

    int query(int x, int l, int r, int ql, int qr, int xl, int xr)
    {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return trees[x].query(xl, xr);
        int mid = (l + r) / 2;
        return query(x * 2, l, mid, ql, qr, xl, xr) + query(x * 2 + 1, mid + 1, r, ql, qr, xl, xr);
    }

    int query(int ql, int qr, int xr, int xl)
    {
        ql = lower_bound(all(realindex), ql) - realindex.begin();
        qr = upper_bound(all(realindex), qr) - realindex.begin() - 1;
        return query(1, 0, n - 1, ql, qr, xr, xl);
    }
};

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
    depth[0] = -1;
    dfs(0, 0);
    activate.resize(n);
    deactivate.resize(n);



    rep(i, sz(trams))
    {
        p2 t = trams[i];
        int l = lca(t.first, t.second);
        activate[t.first].emplace_back(depth[l],t.first);
        activate[t.second].emplace_back(depth[l], t.second);
        deactivate[l].emplace_back(depth[l], t.first);
        deactivate[l].emplace_back(depth[l], t.second);
    }
    dfs2(0, 0);

    vector<p2> times;
    repe(t, trams)
    {
        times.emplace_back(tin[t.first], tin[t.second]);
    }
    Tree2D tree(times);
    
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;

        if (isancestor(a,b)||isancestor(b,a))
        {
            if (isancestor(b, a)) swap(a, b);
            assert(isancestor(a, b));

            if (maxup[b]!=-1&& maxup[b] <= depth[a])
            {
                cout << "Yes\n";
            }
            else cout << "No\n";
            continue;
        }



        bool any = tree.query(tin[a],tout[a],tin[b],tout[b])>0;
        if (!any) any |= tree.query(tin[b],tout[b],tin[a],tout[a])>0;
        
        cout << (any ? "Yes" : "No") << "\n";
    }

    return 0;
}
