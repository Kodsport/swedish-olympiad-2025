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

typedef unsigned long long ull;

const int maxv = 4;


const int blocksize = 300;

const int numblocks = (int(1e5) + blocksize - 1) / blocksize;
ull blocks[numblocks][maxv][maxv+1];


signed main()
{
	fast();

	int n, q;
	cin >> n >> q;
	vector<ull> nums(n);
	rep(i, n) cin >> nums[i];

	// update: O(b*maxv^2)
	// query: O(n/b*maxv^2)
	auto update_block = [&](int b)
		{
			if ((b+1) * blocksize >= n) return;

			ull block[maxv][maxv+1];
			memset(block, 0, sizeof(block));

			ull newrow[maxv + 1];
			repp(i, b * blocksize, (b + 1) * blocksize)
			{
				memset(newrow, 0, sizeof(newrow));
				int v = nums[i];
				newrow[maxv]++;
				rep(o, maxv)
				{
					rep(j, maxv + 1)
					{
						newrow[j] += block[o][j];
					}
				}
				rep(j, maxv) newrow[j]++;
				rep(j, maxv+1) newrow[j] -= block[v][j];
				newrow[v]--;

				rep(j, maxv + 1) block[v][j] += newrow[j];
				
			}
			rep(i,maxv) rep(j,maxv+1) blocks[b][i][j] = block[i][j];
		};

	rep(i, numblocks)
	{
		update_block(i);
	}

	auto solve = [&]()
		{
			ull dp[maxv];
			memset(dp, 0, sizeof(dp));

			ull newdp[maxv];
			rep(b, n / blocksize)
			{
				memset(newdp, 0, sizeof(newdp));
				rep(i, maxv)
				{
					rep(j, maxv)
					{
						newdp[i] += dp[j] * blocks[b][i][j];
					}
					newdp[i] += blocks[b][i][maxv];
				}
				rep(j, maxv) dp[j] += newdp[j];
			}

			int base = n / blocksize;
			ull t = 0;
			rep(i, maxv) t += dp[i];
			repp(i, base*blocksize, n)
			{
				ull s = 1 + t - dp[nums[i]];
				dp[nums[i]] = dp[nums[i]] + s;
				t = t + s;
			}

			cout << 1 + t << "\n";
		};
	solve();

	while (q--)
	{
		int i, v;
		cin >> i >> v;
		i--;
		nums[i] = v;
		update_block(i / blocksize);
		solve();
	}


	return 0;
}
