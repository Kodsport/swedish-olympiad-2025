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

const int maxv = 12;
signed main()
{
	fast();

	int n, q;
	cin >> n >> q;
	vector<ull> nums(n);
	rep(i, n) cin >> nums[i];

	auto solve = [&]()
		{
			vector<ull> dp(maxv);

			rep(i, n)
			{
				ull s = 1;
				rep(j, maxv)
				{
					if (j != nums[i]) s += dp[j];
				}
				dp[nums[i]] = dp[nums[i]] + s;
			}

            ull t = 0;
            rep(j,maxv) t+=dp[j];
			cout << 1 + t << "\n";
		};
	solve();

	while (q--)
	{
		int i, v;
		cin >> i >> v;
		i--;
		nums[i] = v;
		solve();
	}


	return 0;
}
