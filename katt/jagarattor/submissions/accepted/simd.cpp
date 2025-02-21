#include <bitset>
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#include <immintrin.h>
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
vi is_cutvertex, low, num;
vector<tuple<int, int, int>> edge_stk;
vi edge_bcc;

void dfs(int u, int parent, int& timer, vector<vector<p2>>& adj) {
	num[u] = low[u] = ++timer;
	int children = 0;
	for (auto [v, eid] : adj[u]) {
		if (v == parent) continue;
		if (!num[v]) {
			edge_stk.push_back({ u, v, eid });
			children++;
			dfs(v, u, timer, adj);
			low[u] = min(low[u], low[v]);
			if ((parent != -1 && low[v] >= num[u]) || (parent == -1 && children > 1)) {
				is_cutvertex[u] = 1;
				int bcc_id = comps.size();
				vector<int> nodes;
				while (true) {
					auto [x, y, id] = edge_stk.back();
					edge_stk.pop_back();
					nodes.push_back(x);
					nodes.push_back(y);
					edge_bcc[id] = bcc_id;
					if (x == u && y == v)
						break;
				}
				sort(nodes.begin(), nodes.end());
				nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
				comps.push_back(nodes);
			}
		}
		else if (num[v] < num[u]) {
			low[u] = min(low[u], num[v]);
			edge_stk.push_back({ u, v, eid });
		}
	}
}

void bcc(vector<vector<p2>>& adj, int m) {
	int n = adj.size();
	edge_bcc.assign(m, -1);
	is_cutvertex.assign(n, 0);
	num.assign(n, 0);
	low.assign(n, 0);
	int timer = 0;
	for (int i = 0; i < n; i++) {
		if (!num[i]) {
			dfs(i, -1, timer, adj);
			if (!edge_stk.empty()) {
				int bcc_id = comps.size();
				vector<int> nodes;
				while (!edge_stk.empty()) {
					auto [x, y, id] = edge_stk.back();
					edge_stk.pop_back();
					nodes.push_back(x);
					nodes.push_back(y);
					edge_bcc[id] = bcc_id;
				}
				sort(nodes.begin(), nodes.end());
				nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
				comps.push_back(nodes);
			}
		}
	}
}

vi is_cutblock;
vi which_block;
vi which_edge_block;

vector<int> comp_to_block;

vvi block_cut_tree(int m) {
	int n = sz(is_cutvertex);
	which_block.resize(n, -1);
	vector<vector<int>> block_adj;
	int node_id = 0;

	rep(i, n) {
		if (!is_cutvertex[i]) continue;
		which_block[i] = node_id++;
		block_adj.push_back({});
		is_cutblock.push_back(1);
	}

	comp_to_block.resize(sz(comps), -1);

	rep(i, sz(comps)) {
		auto& comp = comps[i];
		int node = node_id++;
		comp_to_block[i] = node;
		block_adj.push_back({});
		is_cutblock.push_back(0);
		for (int u : comp) {
			if (!is_cutvertex[u])
				which_block[u] = node;
			else {
				block_adj[node].push_back(which_block[u]);
				block_adj[which_block[u]].push_back(node);
			}
		}
	}

	which_edge_block.resize(m, -1);
	rep(e, m) {
		which_edge_block[e] = comp_to_block[edge_bcc[e]];
	}

	return block_adj;
}


int dfs3_vis[maxn*2];
int tin[maxn*2];
int tout[maxn*2];
int timer = 0;
int up[20][maxn*2];
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

void toposort(int u, vi& order, vi& vis, vvi& adj)
{
	if (vis[u]) return;
	vis[u] = 1;
	repe(e, adj[u]) toposort(e, order, vis, adj);
	order.push_back(u);
}

void collect_scc(int u, vi& scc, vi& vis, vvi& adj)
{
	if (vis[u]) return;
	vis[u] = 1;
	scc.push_back(u);
	repe(e, adj[u]) collect_scc(e, scc, vis, adj);
}

signed main()
{
	fast();

#if _LOCAL
	ifstream in("c:\\users\\matis\\in.txt");
	cin.rdbuf(in.rdbuf());
#endif

	int n, m, q;
	cin >> n >> m >> q;
	vvi clean_adj(n);
	vector<p2> edges;
	vector<vector<p2>> adj(n);
	vector<vector<p2>> indexed_adj(n);
	rep(i, m)
	{
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		u--; v--; a--; b--;
		adj[u].emplace_back(v, a);
		adj[v].emplace_back(u, b);
		edges.emplace_back(u, v);
		clean_adj[u].push_back(v);
		clean_adj[v].push_back(u);
		indexed_adj[u].emplace_back(v, i);
		indexed_adj[v].emplace_back(u, i);
	}

	bcc(indexed_adj, m);

	vvi block_adj = block_cut_tree(m);
	memset(dfs3_vis, 0, sizeof(dfs3_vis));
	rep(i, sz(block_adj))
	{
		if (!dfs3_vis[i]) dfs3(i, i, block_adj);
	}

	// state in rat graph: either (me, rat) or (leader, rat)
	vvi rat_graph(6 * m);
	vvi rat_graph_rev(6 * m);
	unordered_map<int, int> compress;
	auto hashp = [](int a, int b)
	{
		return a * int(1e6) + b;
	};
	auto get_ind = [&](int a, int b)
	{
		if (compress.count(hashp(a, b))) return compress[hashp(a, b)];
		return compress[hashp(a, b)] = sz(compress);
	};
	int leader = n;
	vi targetnode(n);
	auto add_graph = [&](int a, int b, int c, int d)
	{
		a = get_ind(a, b);
		c = get_ind(c, d);
		rat_graph[a].push_back(c);
		rat_graph_rev[c].push_back(a);
	};
	rep(rat, n)
	{
		targetnode[rat] = leader;
		repe(e, clean_adj[rat])
		{
			add_graph(e, rat, targetnode[rat], rat);
		}
		leader++;
	}

	rep(me, n)
	{
		repe(e, adj[me])
		{
			int rat = e.first;
			add_graph(me, rat, rat, e.second);
		}
	}

	rep(rat, n)
	{
		map<int, vi> groups;
		repe(e, indexed_adj[rat])
		{
			groups[edge_bcc[e.second]].push_back(e.first);
		}

		repe(g, groups)
		{
            if (sz(g.second)==1) continue;
			repe(u, g.second)
			{
				int me = u;

				add_graph(me, rat, leader, rat);
				add_graph(leader, rat, me, rat);
			}
			leader++;
		}
	}

	int rat_sz = sz(compress);
	vi topoorder;
	vi tempvis(rat_sz);
	rep(i, rat_sz) toposort(i, topoorder, tempvis, rat_graph);
	reverse(all(topoorder));
	vvi scc;
	vi which_scc(rat_sz, -1);
	tempvis.assign(rat_sz, 0);
	repe(u, topoorder)
	{
		if (tempvis[u]) continue;
		vi comp;
		collect_scc(u, comp, tempvis, rat_graph_rev);
		repe(v, comp) which_scc[v] = sz(scc);
		scc.push_back(comp);
	}

	vvi scc_adj(sz(scc));
	rep(i, rat_sz)
	{
		repe(e, rat_graph[i])
		{
			int a = which_scc[i];
			int b = which_scc[e];
			if (a != b) scc_adj[a].push_back(b);
		}
	}
	rep(i, sz(scc))
	{
		sort(all(scc_adj[i]));
		scc_adj[i].erase(unique(all(scc_adj[i])), scc_adj[i].end());
	}

	auto scc_ind = [&](int a, int b)
	{
		return which_scc[get_ind(a, b)];
	};

	vector<map<int, int>> cutvertex_block_edge(n);
	rep(i, n)
	{
		if (!is_cutvertex[i]) continue;
		repe(e, indexed_adj[i])
		{
			cutvertex_block_edge[i][which_edge_block[e.second]] = e.first;
		}
	}

	vi ans(q);
	vector<p2> queries(q);
	rep(qind, q)
	{
		int s, r, t;
		cin >> s >> r >> t;
		t--; s--; r--;


		if (!is_cutvertex[r])
		{
			int ad = clean_adj[r][0];
			queries[qind] = p2(scc_ind(ad, r), scc_ind(targetnode[t], t));
		}
		else
		{
			int my_block;
			int block_r = which_block[r];
			int block_s = which_block[s];
			assert(block_r != block_s);
			if (is_ancestor(block_r, block_s))
			{
				my_block = block_s;
				for (int d = 19; d >= 0; d--)
				{
					if (!is_ancestor(up[d][my_block], block_r))
					{
						my_block = up[d][my_block];
					}
				}
			}
			else
			{
				my_block = up[0][block_r];
			}
			assert(!is_cutblock[my_block]);

			assert(my_block != -1);
			assert(cutvertex_block_edge[r].count(my_block));
			int ad = cutvertex_block_edge[r][my_block];
			// ad is any vertex adjacent to the rat that is reachable from s
			queries[qind] = p2(scc_ind(ad, r), scc_ind(targetnode[t], t));
		}
	}

	auto solve = [&ans, &scc_adj, &queries]() {
		int n = sz(scc_adj);

		vi indeg(n);
		rep(i, n) repe(e, scc_adj[i]) indeg[e]++;
		//cerr << n << " " << accumulate(all(indeg), 0LL) << "\n";

		vector<int> topo;
		queue<int> q;
		for (int i = 0; i < n; i++) {
			if (indeg[i] == 0)
				q.push(i);
		}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			topo.push_back(u);
			for (int v : scc_adj[u]) {
				if (--indeg[v] == 0)
					q.push(v);
			}
		}
		reverse(all(topo));

		const int num_process = 680;
		const int blocksize = 64*num_process;
		int blocks = (n + blocksize - 1) / blocksize;

		vector<p2> blocked_queries;
		rep(i, sz(queries)) {
			blocked_queries.emplace_back(queries[i].second / blocksize, i);
		}
		sort(all(blocked_queries));

		int qp = 0;

		auto start =chrono::high_resolution_clock::now();
		vector<p2> edge_topo;
		repe(u, topo) {
			for (int v : scc_adj[u]) {
				edge_topo.emplace_back(u,v);
			}
		}
		vector<array<unsigned long long, num_process>> dp(n);
		for (int b = 0; b < blocks; b++) {
			int low = b * blocksize;
			int high = min(n, (b + 1) * blocksize);

			rep(i, n) rep(j, num_process) dp[i][j] = 0ULL;

			for (int i = low; i < high; i++) {
				int offset = i - low;
				int word = offset / 64;
				int bit = offset % 64;
				dp[i][word] |= (1ULL << bit);
			}

			for (auto [u,v] : edge_topo) {
				for (int i = 0; i < num_process; i += 4) {
					__m256i dp_v = _mm256_loadu_si256((__m256i*)&dp[v][i]);
					__m256i dp_u = _mm256_loadu_si256((__m256i*)&dp[u][i]);
					dp_u = _mm256_or_si256(dp_u, dp_v);
					_mm256_storeu_si256((__m256i*)&dp[u][i], dp_u);
				}
			}

			while (qp < sz(blocked_queries) && blocked_queries[qp].first == b) {
				int ind = blocked_queries[qp].second;
				int u = queries[ind].first;
				int target = queries[ind].second;
				int offset = target - low;
				int word = offset / 64;
				int bit = offset % 64;
				ans[ind] = ((dp[u][word] >> bit) & 1ULL) > 0;
				qp++;
			}
		}
		cerr << (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count()) << "ms";
	};

	solve();
	rep(i, q) cout << ans[i] << "\n";

	return 0;
}
