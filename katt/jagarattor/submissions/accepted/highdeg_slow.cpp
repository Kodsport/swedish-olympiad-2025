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

int vis[2000][2000];
int visver = 10;
signed main()
{
	fast();

	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<p2>> adj(n);
	vvi mat(n, vi(n));
	rep(i, m)
	{
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		u--; v--; a--; b--;
		adj[u].emplace_back(v, a);
		adj[v].emplace_back(u, b);
		mat[u][v] = 1;
		mat[v][u] = 1;
	}

	auto colorbfs = [&](int blocked)
	{
		vi color(n, -1);
		int c = 0;
		rep(i, n)
		{
			if (i == blocked) continue;
			queue<int> q;
			q.emplace(i);
			while (sz(q))
			{
				int u = q.front(); q.pop();
				if (color[u] != -1)continue;
				color[u] = c;
				repe(e, adj[u])
				{
					if (e.first != blocked) q.emplace(e.first);
				}
			}
			c++;
		}
		
		return color;
	};

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


	vvi switch_back;
	vector<map<int,int>> rat_switches(n);
	rep(i, n)
	{
		vi colors = colorbfs(i);

		map<int, vi> groups;
		repe(e, adj[i])
		{
			groups[colors[e.first]].push_back(e.first);
		}

		repe(g, groups)
		{
			int leader = sz(switch_back);
			switch_back.push_back({});
			repe(u, g.second)
			{
				switch_back[leader].emplace_back(u);
				rat_switches[i][u] = leader+n;
			}
		}
	}

	memset(vis, 0, sizeof(vis));
	while (q--)
	{
		visver++;
		int s, r, t;
		cin >> s >> r >> t;
		t--; s--; r--;


		// O(M)
		vi reachable = bfs(s, r);

		queue<pair<int, int>> q;
		repe(e, adj[r]) if (reachable[e.first]) q.emplace(e.first, r);

		bool possible = 0;

		while (sz(q))
		{
			int me, rat;
			tie(me, rat) = q.front();
			q.pop();

			assert(me>=n || mat[me][rat]);

			if (vis[me][rat]==visver) continue;
			vis[me][rat] = visver;
			if (me>=n)
			{
				me -= n;
				repe(e, switch_back[me])
				{
					q.emplace(e, rat);
				}
				continue;
			}

			if (rat == t)
			{
				possible = 1;
				break;
			}

			if (rat_switches[rat].count(me)) q.emplace(rat_switches[rat][me], rat);

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
