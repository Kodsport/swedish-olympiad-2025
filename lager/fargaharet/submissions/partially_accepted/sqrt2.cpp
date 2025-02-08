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

const int blocksize = 300;
const int numblocks = (int(1e5) + blocksize - 1) / blocksize;
ull blocks[numblocks][2][3];

signed main()
{
	fast();

	int n, q;
	cin >> n >> q;
	vector<ull> nums(n);
	rep(i, n) cin >> nums[i];


	auto update_block = [&](int b)
		{
			if ((b+1) * blocksize >= n) return;

			ull block[2][3];
			memset(block, 0, sizeof(block));

			repp(i, b * blocksize, (b + 1) * blocksize)
			{
				if (nums[i]==0)
				{
					block[0][0] += block[1][0];
					block[0][1] += block[1][1];
					block[0][2] += block[1][2];
					
					block[0][2]++;
					block[0][1]++;
				}
				else
				{
					block[1][0] += block[0][0];
					block[1][1] += block[0][1];
					block[1][2] += block[0][2];

					block[1][2]++;
					block[1][0]++;
				}
				
				
			}
			rep(i,2) rep(j,3) blocks[b][i][j] = block[i][j];
		};

	rep(i, numblocks)
	{
		update_block(i);
	}

	auto solve = [&]()
		{
			ull dp[2];
			memset(dp, 0, sizeof(dp));

			rep(b, n / blocksize)
			{
				ull newdp[2] = { 0,0 };
				rep(i, 2)
				{
					newdp[i] = dp[0] * blocks[b][i][0] + dp[1] * blocks[b][i][1] + blocks[b][i][2];
				}
				dp[0] += newdp[0];
				dp[1] += newdp[1];
			}

			int base = n / blocksize;
			ull t = dp[0] + dp[1];
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
