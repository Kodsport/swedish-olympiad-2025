// O(2^(NM)NM) per update
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

	int n, m, q;
	cin >> n >> m >> q;
	assert(n * m <= 20);
	vvi grid(n, vi(m));
	rep(i, n) rep(j, m) cin >> grid[i][j];
	p2 start;
	rep(i, n) rep(j, m) if (grid[i][j] == 0) start = p2(i, j);
	vvi cnt(n, vi(m));
	bool anyvalid = 0;
	vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
	auto compute = [&]()
		{
			anyvalid = 0;
			rep(i, n) rep(j, m) cnt[i][j] = 0;
			vvi dist(n, vi(m, inf));
			rep(mask, 1 << (n * m))
			{
				rep(i, n) rep(j, m) dist[i][j] = inf;
				queue<pair<int, p2>> q;
				q.emplace(0, start);
				dist[start.first][start.second] = 0;
				while (sz(q))
				{
					int d;
					p2 p;
					tie(d, p) = q.front();
					q.pop();
					if (d > dist[p.first][p.second]) continue;
					if (dist[p.first][p.second] != grid[p.first][p.second]) break;
					if (mask & (1 << (p.first * m + p.second))) continue;

					repe(dir, dirs)
					{
						p2 np = p2(p.first + dir.first, p.second + dir.second);
						if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= m) continue;
						if (d+1<dist[np.first][np.second])
						{
							dist[np.first][np.second] = d + 1;
							q.emplace(d + 1, np);
						}
					}
				}
				rep(i, n) rep(j, m) if (dist[i][j] == inf) dist[i][j] = -1;
				if (dist==grid)
				{
					anyvalid = 1;
					rep(i, n) rep(j, m)
					{
						if (mask & (1 << (i * m + j))) cnt[i][j]++;
					}
				}
			}
		};

	compute();
	while (q--)
	{
		char t;
		cin >> t;
		if (t=='?')
		{
			int r, c;
			cin >> r >> c;
			r--; c--;
			if (!anyvalid)
			{
				cout << "fel\n";
			}
			else
			{
				if (cnt[r][c] == 1 << (n * m)) cout << "ja\n";
				else if (cnt[r][c]) cout << "kanske\n";
				else cout << "nej\n";
			}
		}
		else
		{
			int r, c, v;
			cin >> r >> c >> v;
			r--; c--;
			grid[r][c] = v;
			compute();
		}
	}

	return 0;
}
