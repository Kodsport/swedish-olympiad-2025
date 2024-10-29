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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const int maxr = 500;
const int maxn = maxr * maxr;
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

int tin[maxn];
int tout[maxn];
int timer = 0;
int up[20][maxn];
void dfs3(int u, int p, vvi& adj)
{
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


signed main()
{
	fast();

	int r, c, Q;
	cin >> r >> c >> Q;
	vector<string> grid(r);
	rep(i, r) cin >> grid[i];

	vvi queries;
	p2 goal;
	while (Q--)
	{
		vi query(6);
		rep(i, 6) cin >> query[i], query[i]--;
		queries.push_back(query);
		goal = p2(query[4], query[5]);
	}

	vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

	auto isgood = [&](p2 x)
	{
		if (x.first < 0 || x.second < 0 || x.first >= r || x.second >= c || grid[x.first][x.second] == '#') return false;
		return true;
	};

	auto flatten = [&](p2 x)
	{
		return x.first * c + x.second;
	};

	vvi adj(r * c);
	rep(i, r) rep(j, c)
	{
		if (grid[i][j] == '#') continue;
		repe(dir, dirs)
		{
			p2 np = p2(i + dir.first, j + dir.second);
			if (!isgood(np)) continue;
			p2 pos = p2(i, j);
			adj[flatten(np)].push_back(flatten(pos));
			adj[flatten(pos)].push_back(flatten(np));
		}
	}


	bcc(adj);

	vvi block_adj = block_cut_tree();
	dfs3(0, 0, block_adj);


	vi dp(4*r*c);
	
	vvi r_box_adj(4 * r * c);

	auto flatten_2 = [&](p2 pos, int d)
	{
		return pos.first + pos.second * r + d * r * c;
	};

	rep(i, r) rep(j, c)
	{
		p2 box = p2(i, j);
		rep(d, 4)
		{
			p2 my_pos = p2(box.first + dirs[d].first, box.second + dirs[d].second);
			if (!isgood(my_pos)) continue;
			// change side
			rep(d2, 4)
			{
				p2 new_side = p2(box.first + dirs[d2].first, box.second + dirs[d2].second);
				if (!isgood(new_side)) continue;
				if (cangoto(flatten(my_pos), flatten(new_side), flatten(box)))
				{
					r_box_adj[flatten_2(box, d2)].push_back(flatten_2(box, d));
				}
			}

			// push box
			{
				p2 np = p2(box.first - dirs[d].first, box.second - dirs[d].second);
				if (isgood(np)) r_box_adj[flatten_2(np, d)].push_back(flatten_2(box, d));
			}
		}
	}


	rep(dstart, 4)
	{
		p2 delta = p2(goal.first + dirs[dstart].first, goal.second + dirs[dstart].second);
		if (!isgood(delta)) continue;
		queue<int> q;
		q.emplace(flatten_2(goal, dstart));
		while (sz(q))
		{
			int u = q.front();
			q.pop();

			if (dp[u]) continue;
			dp[u] = 1;

			repe(e, r_box_adj[u])
			{
				assert(e != flatten_2(p2(4, 0), 2));
				assert(e != flatten_2(p2(4, 0), 1));
				q.emplace(e);
			}
		}
	}

	repe(query, queries)
	{
		p2 start = p2(query[0], query[1]);
		p2 box = p2(query[2], query[3]);

		bool possible = 0;
		rep(d, 4)
		{
			p2 t = p2(box.first + dirs[d].first, box.second + dirs[d].second);
			if (!isgood(t)) continue;
			if (!cangoto(flatten(start), flatten(t), flatten(box))) continue;
			if (dp[flatten_2(box, d)])
			{
				possible = 1;
			}
		}

		cout << (possible ? "Ja" : "Nej") << "\n";
	}

	return 0;
}
