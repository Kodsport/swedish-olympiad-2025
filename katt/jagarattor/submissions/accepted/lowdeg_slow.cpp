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

int visver = 0;
int vis[1000][1000];
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
				if (!vis[e.first] && e.first != blocked) vis[e.first]=1,q.emplace(e.first);
			}
		}
		return vis;
	};

	// for each vertex (rat) and neighbour, which neighbours can i reach?
	// O(M*deg^2)
	vector<vvi> neighbourtransitions(n);
	rep(i, n)
	{
		vvi trans(sz(adj[i]));
		rep(j, sz(adj[i]))
		{
			p2 e = adj[i][j];
			vi transitions;
			int u = e.first;
			vi reachable = bfs(u, i);
			repe(e2, adj[i])
			{
				if (reachable[e2.first])
				{
					transitions.push_back(e2.first);
				}
			}
			trans[j]=transitions;
		}
		neighbourtransitions[i] = trans;
	}

	auto findmyind = [&](int root, int b)
	{
		rep(j, sz(adj[root])) if (adj[root][j].first == b) return j;
		assert(0);
	};

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

			assert(mat[me][rat]);

			if (vis[me][rat]==visver) continue;
			vis[me][rat] = visver;

			if (rat == t)
			{
				possible = 1;
				break;
			}

			repe(e, adj[me])
			{
				if (e.first == rat)
				{
					q.emplace(e.first, e.second);
				}
			}

			int myind = findmyind(rat, me);
			repe(t, neighbourtransitions[rat][myind])
			{
				q.emplace(t, rat);
			}
		}

		cout << possible << "\n";
	}


	return 0;
}
