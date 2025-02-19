//@EXPECTED_GRADES@ AC AC RTE TLE TLE RTE
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

signed main()
{
	fast();

	int cangofrom[4][4][30][30];

	int r, c, Q;
	cin >> r >> c >> Q;
	vector<string> grid(r);
	rep(i, r) cin >> grid[i];

	vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

	auto isgood = [&](p2 x)
	{
		if (x.first < 0 || x.second < 0 || x.first >= r || x.second >= c || grid[x.first][x.second] == '#') return false;
		return true;
	};

	auto bfs = [&](p2 start, p2 box)
	{
		queue<p2> q;
		q.emplace(start);
		vvi vis(r, vi(c));
		while (sz(q))
		{
			p2 p = q.front();
			q.pop();
			if (vis[p.first][p.second]) continue;
			vis[p.first][p.second] = 1;

			repe(dir, dirs)
			{
				p2 np = p2(p.first + dir.first, p.second + dir.second);
				if (!isgood(np)) continue;
				if (np == box) continue;
				q.emplace(np);
			}
		}
		return vis;
	};

	rep(i, r) rep(j, c)
	{
		if (grid[i][j] == '#') continue;

		

		p2 box = p2(i, j);
		rep(d, 4)
		{
			p2 dir = dirs[d];
			p2 np = p2(i + dir.first, j + dir.second);
			if (!isgood(np)) continue;
			vvi vis = bfs(np, box);
			rep(d2, 4)
			{
				dir = dirs[d2];
				np = p2(i + dir.first, j + dir.second);
				if (!isgood(np)) continue;
				if (vis[np.first][np.second])
				{
					cangofrom[d][d2][i][j] = 1;
				}
			}
		}
	}

	int dp[4][30][30];
	while (Q--)
	{
		memset(dp, 0, sizeof(dp));
		vi query(6);
		rep(i, 6) cin >> query[i], query[i]--;
		p2 start = p2(query[0], query[1]);
		p2 box = p2(query[2], query[3]);
		p2 goal = p2(query[4], query[5]);

		queue<pair<p2, int>> q;
		vvi vis = bfs(start, box);
		rep(d, 4)
		{
			p2 dir = dirs[d];
			p2 np = p2(box.first + dir.first, box.second + dir.second);
			if (!isgood(np)) continue;
			if (vis[np.first][np.second])
			{
				q.emplace(box, d);
			}
		}

		bool possible = 0;
		while (sz(q))
		{
			p2 box;
			int d;
			tie(box, d) = q.front();
			q.pop();

			if (dp[d][box.first][box.second]) continue;
			dp[d][box.first][box.second] = 1;

			if (box == goal)
			{
				possible = 1;
				break;
			}

			rep(d2, 4)
			{
				if (cangofrom[d][d2][box.first][box.second])
				{
					q.emplace(box, d2);
				}
			}

			{
				p2 np = p2(box.first - dirs[d].first, box.second - dirs[d].second);
				if (isgood(np)) q.emplace(np, d);
			}
		}

		cout << (possible ? "Ja" : "Nej") << "\n";
	}

	return 0;
}
