// ~1.3e5 matrices
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

const int matsz = 2*(maxv + 1);
struct matblock
{
	ull mat[matsz][matsz];
	matblock()
	{
		memset(mat, 0, sizeof(mat));
	}

	matblock operator*(const matblock& B) {
		matblock result;
		for (int i = 0; i < matsz; ++i) {
			for (int k = 0; k < matsz; ++k) {
				for (int j = 0; j < matsz; ++j) {
					result.mat[i][j] += mat[i][k] * B.mat[k][j];
				}
			}
		}
		return result;
	}
};
matblock unit;
matblock mats[maxv+1];

vector<ull> nums;
struct Tree {
	typedef matblock T;
	vector<T> s; int n = 1 << 17;
	Tree(int N)
	{
		s.resize(n, unit);
		/*rep(i, N) s[i + n] = mats[nums[i]];
		for (int i = n - 1; i > 0; i--)
		{
			s[i] = s[i * 2] * s[i * 2 + 1];
		}*/
	}
	void update(int pos, T val) {
		pos = (pos + n) / 2;
		s[pos] = mats[nums[pos * 2 - n]] * mats[nums[pos * 2 + 1 - n]];
		while (pos /= 2)
			s[pos] = s[pos * 2] * s[pos * 2 + 1];
	}
};

signed main()
{
	fast();

#if 0&&_LOCAL
	ifstream in("e:/in.txt");
	cin.rdbuf(in.rdbuf());
#endif

	rep(v, maxv)
	{
		matblock el;
		rep(i, matsz) el.mat[i][i] += 1;
		rep(i, maxv + 1) el.mat[maxv + 1 + i][maxv] += 1;
		el.mat[maxv + 1 + v][maxv] -= 1;

		rep(i, maxv + 1) el.mat[maxv + 1 + i][v] += 1;
		el.mat[maxv + 1 + v][v] -= 1;
		el.mat[v][maxv] += -1;
		el.mat[maxv][maxv] += 1;
		el.mat[v][v] -= 1;
		el.mat[maxv][v] += 1;
		mats[v] = el;
	}

	int n, q;
	cin >> n >> q;
	nums.resize(n);
	rep(i, n) cin >> nums[i];

	//rep(i, maxv + 1) unit.mat[i][maxv + 1 + i] = 1;
	rep(i, matsz) unit.mat[i][i] = 1;
	mats[maxv] = unit;
	while (sz(nums)<(1<<17))
	{
		nums.push_back(maxv);
	}

	Tree tree(n);

	auto update = [&](int i)
		{
			int v = nums[i];
			
			tree.update(i, mats[nums[i]]);
		};
	rep(i, n) update(i);

	auto solve = [&]()
		{
			cout << tree.s[1].mat[maxv][maxv] << "\n";
		};
	solve();

	while (q--)
	{
		int i, v;
		cin >> i >> v;
		i--;
		nums[i] = v;
		update(i);
		solve();
	}

	return 0;
}
