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

ull dp[1000][1001];
ull dpd[1000][1001];
int n;
vi nums;
ull count(int i, int p)
{
	if (i==n)
	{
		return 1;
	}

    if (dpd[i][p+1]) return dp[i][p+1];

	ull ret = 0;

	ret += count(i+1,p);
	if (p == -1 || (p != -1 && nums[i] != nums[p])) ret += count(i + 1, i);

    dpd[i][p+1]=1;
	return dp[i][p+1] = ret;
}

signed main()
{
	fast();
	memset(dp, -1, sizeof(dp));
    memset(dpd,0,sizeof(dpd));

	int q;
	cin >> n >> q;
	nums.resize(n);
	rep(i, n) cin >> nums[i];

	cout << count(0, -1);

	return 0;
}
