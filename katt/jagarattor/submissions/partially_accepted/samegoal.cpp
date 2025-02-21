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

signed main()
{
	fast();

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

	//repe(e, edges) cout << e.first << " " << e.second << "\n";

	bcc(indexed_adj, m);


	vvi block_adj = block_cut_tree(m);
	memset(dfs3_vis, 0, sizeof(dfs3_vis));
	rep(i, sz(block_adj))
	{
		if (!dfs3_vis[i]) dfs3(i, i, block_adj);
	}

	// state in rat graph: either (me, rat) or (leader, rat)
	vvi rat_graph(4 * m);
	vvi rat_graph_rev(4 * m);
	vi rat_pos(4 * m);
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
	rep(me, n)
	{
		repe(e, adj[me])
		{
			// state (me,rat)
			int rat = e.first;
			rat_pos[get_ind(me, rat)] = rat;
			rat_pos[get_ind(rat, e.second)] = e.second;
			rat_graph[get_ind(me, rat)].push_back(get_ind(rat, e.second));
			rat_graph_rev[get_ind(rat, e.second)].push_back(get_ind(me, rat));
		}
	}

	int leader = n;
	rep(rat, n)
	{
		map<int, vi> groups;
		repe(e, indexed_adj[rat])
		{
			groups[edge_bcc[e.second]].push_back(e.first);
		}

		repe(g, groups)
		{
			repe(u, g.second)
			{
				int me = u;
				rat_pos[get_ind(me, rat)] = rat;
				rat_pos[get_ind(leader, rat)] = rat;

				rat_graph[get_ind(me, rat)].push_back(get_ind(leader, rat));
				rat_graph[get_ind(leader, rat)].push_back(get_ind(me, rat));
				rat_graph_rev[get_ind(me, rat)].push_back(get_ind(leader, rat));
				rat_graph_rev[get_ind(leader, rat)].push_back(get_ind(me, rat));
			}
			leader++;
		}
	}

	int t;
	vector<p2> queries;
	while (q--)
	{
		int s, r;
		cin >> s >> r >> t;
		t--; s--; r--;
		queries.emplace_back(s, r);
	}

	vi reachable(sz(compress));
	{
		queue<int> q;

		repe(e, adj[t]) q.emplace(get_ind(e.first, t));

		while (sz(q))
		{
			int u = q.front();
			q.pop();

			if (reachable[u]) continue;
			reachable[u] = 1;

			repe(e, rat_graph_rev[u])
			{
				q.emplace(e);
			}
		}
	}

	vector<map<int, int>> cutvertex_block_edge(n);
	rep(i, n)
	{
		if (!is_cutvertex[i]) continue;
		repe(e, indexed_adj[i])
		{
			cutvertex_block_edge[i][which_edge_block[e.second]] = e.first;
		}
	}

	repe(qu, queries)
	{
		int s, r;
		tie(s, r) = qu;
		if (!is_cutvertex[r])
		{
			int ad = clean_adj[r][0];
			cout << reachable[get_ind(ad, r)] << "\n";
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
			cout << reachable[get_ind(ad, r)] << "\n";
		}
	}


	return 0;
}
