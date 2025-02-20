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

signed main()
{
	fast();

	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<p2>> adj(n);
	rep(i, m)
	{
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		u--; v--; a--; b--;
		adj[u].emplace_back(v, a);
		adj[v].emplace_back(u, b);
	}

	int vis[500][500];
	while (q--)
	{
		memset(vis, 0, sizeof(vis));
		int s, r, t;
		cin >> s >> r >> t;
		t--; s--; r--;

		queue<pair<int, int>> q;
		q.emplace(s, r);

		bool possible = 0;

		while (sz(q))
		{
			int me, rat;
			tie(me, rat) = q.front();
			q.pop();

			if (vis[me][rat]) continue;
			vis[me][rat] = 1;

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
				else
				{
					q.emplace(e.first, rat);
				}
			}
		}

		cout << possible << "\n";
	}


	return 0;
}
