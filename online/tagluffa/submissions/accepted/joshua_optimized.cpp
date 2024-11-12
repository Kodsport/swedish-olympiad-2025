// O(NlogN+NKlogN+K^2logN)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef uint32_t tempint;

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

vector<vector<p2>> adj;

struct centroid
{
    vvi children;
    vector<vi> par_dist;
    vi par;
    vi size;
    centroid() : children(sz(adj)), par(sz(adj)), par_dist(sz(adj)), size(sz(adj))
    {
        init_centroid(0, -1);
    }

    void calc_sz(int u, int p)
    {
        size[u] = 1;
        repe(e, adj[u]) if (e.first != p) calc_sz(e.first, u), size[u] += size[e.first];
    }

    int find_centroid(int u, int p, int n)
    {
        repe(e, adj[u]) if (e.first != p && size[e.first] > n / 2) return find_centroid(e.first, u, n);
        return u;
    }

    void calc_dist(int u, int p, int d)
    {
        par_dist[u].emplace_back(d);
        repe(e, adj[u]) if (e.first != p) calc_dist(e.first, u, d + e.second);
    }

    void init_centroid(int u, int p)
    {
        calc_sz(u, -1);
        u = find_centroid(u, -1, size[u]);
        calc_dist(u, -1, 0);
        par[u] = p;
        if (p != -1) children[p].push_back(u);
        repe(e, adj[u])
        {
            auto it = adj[e.first].begin();
            while (it->first != u) it = next(it);
            adj[e.first].erase(it);
            init_centroid(e.first, u);
        }
    }
};

const int lomask = (1 << 20) - 1;

struct fenwick
{
    int n;
    vector<p2> tree;
    fenwick(int n) : n(n), tree(n + 1) {}
    fenwick() {}

    p2 f(const p2& a, const p2& b)
    {
        int max1 = 0, max2 = 0;

        for (int val : {a.first, a.second, b.first, b.second}) {
            if ((val & lomask) > (max1 & lomask)) {
                if ((max1 >> 20) != (max2 >> 20))
                {
                    max2 = max1; // update second largest
                }

                max1 = val;  // update largest
            }
            else if ((val & lomask) > (max2 & lomask) && (val >> 20) != (max2 >> 20)) {
                max2 = val;  // update second largest if it's not the largest
            }
        }

        return p2(max1, max2);
    }

    void update(int r, p2 v)
    {
        r = n - 1 - r;
        for (r++; r < sz(tree); r += (r & -r)) tree[r] = f(tree[r], v);
    }

    p2 query(int l) // query [l, n)
    {
        p2 ret = p2(0, 0);
        int r = n - 1 - l;
        for (r++; r > 0; r -= (r & -r)) ret = f(tree[r], ret);
        return ret;
    }
};

signed main()
{
    fast();

    int n, k;
    cin >> n >> k;
    adj.resize(n);
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
        trains.emplace_back(t + d, a, b, d);
    }

    sort(all(trains));
    reverse(all(trains));

    centroid decomp;

    vi par = decomp.par;
    vvi& par_dist = decomp.par_dist;
    rep(i, n) reverse(all(par_dist[i]));
    vvi& children = decomp.children;
    vi unique_values(n);
    vvi values(n);
    vector<vector<p2>> child_index(n);
    rep(i, n)
    {
        children[i].push_back(-1);

        repe(c, children[i])
        {
            child_index[i].emplace_back(c, sz(child_index) + 1);
        }
        sort(all(child_index[i]));
    }

    auto add_nodes = [&](int u, int t)
        {
            int c = u;
            int prevc = -1;
            int i = 0;
            while (c != -1)
            {
                unique_values[c]++;
                values[c].push_back(t - par_dist[u][i]);
                prevc = c;
                c = par[c];
                i++;
            }
        };

    repe(tr, trains)
    {
        int t, a, b, d;
        tie(t, a, b, d) = tr;

        add_nodes(a, t - d);
    }
    add_nodes(0, inf);
    rep(i, n) sort(all(values[i]));

    vector<fenwick> trees(n);
    rep(i, n)
    {
        trees[i] = fenwick(unique_values[i]);
    }

    auto add = [&](int u, int t, int dpv)
        {
            int c = u;
            int prevc = -1;
            int i = 0;
            while (c != -1)
            {
                int realt = t - par_dist[u][i];
                int ind = lower_bound(all(values[c]), realt) - values[c].begin();
                int ignore_ind = lower_bound(all(child_index[c]), p2(prevc, inf)) - child_index[c].begin();
                trees[c].update(ind, p2(dpv + (ignore_ind << 20), 0));
                prevc = c;
                c = par[c];
                i++;
            }
        };

    auto query = [&](int u, int t)
        {
            int ret = -inf;
            int c = u;
            int prevc = -1;
            int i = 0;
            while (c != -1)
            {
                int ignoreind = prevc == -1 ? inf : lower_bound(all(child_index[c]), p2(prevc, inf)) - child_index[c].begin();
                int realt = t + par_dist[u][i];
                int ind = lower_bound(all(values[c]), realt) - values[c].begin();

                if (ind != unique_values[c])
                {
                    p2 res = trees[c].query(ind);
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
                i++;
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
            add(a, t - d, best + 1);
        }

    }

    rep(i, n)
    {
        cout << query(i, 0) << " ";
    }
    cout << endl;


    return 0;
}
