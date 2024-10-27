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

	int r, c, Q;
	cin >> r >> c >> Q;
	vector<string> grid(r);
	rep(i, r) cin >> grid[i];

	int vis[30][30][30][30];
	vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
	while (Q--)
	{
		memset(vis, 0, sizeof(vis));
		vi query(6);
		rep(i, 6) cin >> query[i], query[i]--;
		p2 start = p2(query[0], query[1]);
		p2 box = p2(query[2], query[3]);
		p2 goal = p2(query[4], query[5]);


		queue<pair<p2, p2>> q;
		q.emplace(start, box);

		bool possible = 0;

		while (sz(q))
		{
			p2 me, box;
			tie(me, box) = q.front();
			q.pop();

			if (vis[me.first][me.second][box.first][box.second]) continue;
			vis[me.first][me.second][box.first][box.second] = 1;

			if (box==goal)
			{
				possible = 1;
				break;
			}

			repe(dir, dirs)
			{
				p2 np = p2(me.first + dir.first, me.second + dir.second);

				if (np.first < 0 || np.second < 0 || np.first >= r || np.second >= c || grid[np.first][np.second] == '#') continue;
				if (np != box)
				{
					q.emplace(np, box);
				}
				else
				{
					p2 nbox = p2(box.first + dir.first, box.second + dir.second);
					if (nbox.first < 0 || nbox.second < 0 || nbox.first >= r || nbox.second >= c || grid[nbox.first][nbox.second] == '#') continue;

					q.emplace(np, nbox);
				}
			}
		}

		cout << (possible ? "Ja" : "Nej") << "\n";
	}

	return 0;
}
