// no real optimizations
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


struct Tree {
	vector<matblock> tree;
	Tree(int n) : tree(n*4, unit) {}

	void update(int x, int l, int r, int i, matblock& v)
	{
		if (l == r) return void(tree[x] = v);
		int mid = (l + r) / 2;
		if (i <= mid) update(x * 2, l, mid, i, v);
		else update(x * 2 + 1, mid + 1, r, i, v);
		tree[x] = tree[x * 2] * tree[x * 2 + 1];
	}
};

signed main()
{
	fast();

#if 0&&_LOCAL
	ifstream in("e:/in.txt");
	cin.rdbuf(in.rdbuf());
#endif

	int n, q;
	cin >> n >> q;
	vector<ull> nums(n);
	rep(i, n) cin >> nums[i];

	rep(i, maxv + 1) unit.mat[i][maxv + 1 + i] = 1;

	Tree tree(n);

	auto update = [&](int i)
		{
			int v = nums[i];
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
			tree.update(1,0,n-1,i, el);
		};

	rep(i, n) update(i);

	auto solve = [&]()
		{
			cout << tree.tree[1].mat[maxv][maxv]<<"\n";
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
