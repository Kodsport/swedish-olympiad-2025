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

const int maxn = 1e5;

vector<vector<int>> comps;
vi is_cutvertex, low, num, stk;
void dfs(int u, int p, int& timer, vvi& adj) {
	num[u] = low[u] = ++timer;
	stk.push_back(u);
	for (int e : adj[u]) if (e != p) {
		if (num[e]) low[u] = min(low[u], num[e]);
		else {
			dfs(e, u, timer, adj);
			low[u] = min(low[u], low[e]);
			if (low[e] < num[u]) continue;
			is_cutvertex[u] = (num[u] > 1 || num[e] > 2);
			comps.push_back({ u });
			while (comps.back().back() != e) {
				comps.back().push_back(stk.back());
				stk.pop_back();
			}
		}
	}
};

void bcc(vvi& adj) {
	is_cutvertex.assign(sz(adj), 0);
	num.assign(sz(adj), 0);
	low.assign(sz(adj), 0);
	int timer = 0;
	rep(i, sz(adj)) {
		if (!num[i]) dfs(i, i, timer, adj);
	}
}

vi which_block;
vvi block_cut_tree() {
	int n = sz(is_cutvertex);
	which_block.resize(n, -1);
	vector<vector<int>> block_adj(1);
	int node_id = 0;
	rep(i, n) {
		if (!is_cutvertex[i]) continue;
		which_block[i] = node_id++;
		block_adj.push_back({});
	}

	for (auto& comp : comps) {
		int node = node_id++;
		block_adj.push_back({});
		for (int u : comp) {
			if (!is_cutvertex[u]) which_block[u] = node;
			else {
				block_adj[node].push_back(which_block[u]);
				block_adj[which_block[u]].push_back(node);
			}
		}
	}
	return block_adj;
}

int dfs3_vis[maxn];
int tin[maxn];
int tout[maxn];
int timer = 0;
int up[20][maxn];
void dfs3(int u, int p, vvi& adj)
{
	dfs3_vis[u] = 1;
	tin[u] = timer++;
	up[0][u] = p;
	repp(d, 1, 20) up[d][u] = up[d - 1][up[d - 1][u]];

	repe(e, adj[u]) if (e != p) dfs3(e, u, adj);

	tout[u] = timer++;
}

bool is_ancestor(int a, int b)
{
	return tin[a] <= tin[b] && tin[b] <= tout[a];
}

int lca(int a, int b)
{
	if (is_ancestor(a, b)) return a;
	if (is_ancestor(b, a)) return b;
	for (int d = 19; d >= 0; d--)
	{
		if (!is_ancestor(up[d][a], b))
		{
			a = up[d][a];
		}
	}
	return up[0][a];
}

int cangoto(int a, int b, int c) // is there path a <-> b if we remove c?
{
	if (a == c || b == c) return false;
	if (!is_cutvertex[c]) return true;
	a = which_block[a];
	b = which_block[b];
	c = which_block[c];
	bool anc_a = is_ancestor(c, a);
	bool anc_b = is_ancestor(c, b);
	if (anc_a != anc_b) return false;
	if (!anc_a && !anc_b) return true;
	int lc = lca(a, b);
	if (lc == c) return false;
	if (!is_ancestor(c, lc)) return false;
	return true;
}

void dfs4(int u, int c, vi& vis, vi& which_comp, vvi& adj)
{
	if (vis[u]) return;
	vis[u] = 1;
	which_comp[u] = c;
	repe(e, adj[u]) dfs4(e, c, vis, which_comp, adj);
}

signed main()
{
	fast();

	int n, m, q;
	cin >> n >> m >> q;
	vvi clean_adj(n);
	vector<vector<p2>> adj(n);
	rep(i, m)
	{
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		u--; v--; a--; b--;
		adj[u].emplace_back(v, a);
		adj[v].emplace_back(u, b);
		clean_adj[u].push_back(v);
		clean_adj[v].push_back(u);
	}


	vi vis(n);
	vi which_comp(n);
	int cnt = 0;
	rep(i, n)
	{
		if (vis[i]) continue;
		dfs4(i, cnt++, vis, which_comp, clean_adj);
	}

	bcc(clean_adj);

	vvi block_adj = block_cut_tree();
	memset(dfs3_vis, 0, sizeof(dfs3_vis));
	rep(i, sz(block_adj))
	{
		if (!dfs3_vis[i]) dfs3(i, i, block_adj);
	}

	auto bfs = [&](int u, int blocked)
	{
		vi vis(n);
		queue<int> q;
		q.emplace(u);
		vis[u] = 1;
		while (sz(q))
		{
			int u = q.front(); q.pop();
			repe(e, adj[u])
			{
				if (!vis[e.first] && e.first != blocked) vis[e.first] = 1, q.emplace(e.first);
			}
		}
		return vis;
	};


	while (q--)
	{
		int s, r, t;
		cin >> s >> r >> t;
		t--; s--; r--;


		// O(M)
		vi reachable = bfs(s, r);

		queue<pair<int, int>> q;
		repe(e, adj[r]) if (reachable[e.first]) q.emplace(e.first, r);

		bool possible = 0;
		set<p2> vis;
		while (sz(q))
		{
			int me, rat;
			tie(me, rat) = q.front();
			q.pop();


			if (vis.count(p2(me, rat))) continue;
			vis.emplace(me, rat);

			if (rat == t)
			{
				possible = 1;
				break;
			}

			repe(e, adj[rat])
			{
				if (cangoto(me, e.first, rat))
				{
					q.emplace(e.first, rat);
				}
			}

			repe(e, adj[me])
			{
				if (e.first == rat)
				{
					q.emplace(e.first, e.second);
				}
			}
		}

		cout << possible << "\n";
	}


	return 0;
}
