// saves factor 2 by building segtree in O(N) + faster matrix mult
#pragma GCC optimize("Ofast,inline")
#pragma GCC target("avx2")
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

const int maxv = 10;

const int matsz = maxv + 1;
struct matblock
{
	ull mat[matsz][matsz];
	matblock()
	{
		memset(mat, 0, sizeof(mat));
	}

	matblock operator*(const matblock& B) {
		matblock result;
		matblock transpose;
		rep(i, matsz) rep(j, matsz) transpose.mat[i][j] = B.mat[j][i];
		rep(i, matsz)
		{
			rep(j, matsz)
			{
				int t = 0;
#pragma GCC ivdep
				rep(k, matsz)
				{
					t += mat[i][k] * transpose.mat[j][k];
				}
				result.mat[i][j] = t;
			}
		}
		return result;
	}
	matblock operator+(const matblock& B) {
		matblock result;
		
		rep(i, matsz)
		{
			rep(j, matsz)
			{
				result.mat[i][j] = mat[i][j] + B.mat[i][j];
			}
		}
		return result;
	}
};
pair<matblock, matblock> unit;
pair<matblock, matblock> mats[maxv];

pair<matblock, matblock> merge(pair<matblock, matblock>& a, pair<matblock, matblock>& b)
{
	return make_pair(a.first * b.first, a.second * b.first + b.second);
}

vector<ull> nums;
struct Tree {
	vector<pair<matblock, matblock>> tree;
	Tree(int n) : tree(n * 4, unit)
	{
		build(1, 0, n - 1);
	}

	void build(int x, int l, int r)
	{
		if (l == r)
		{
			return void(tree[x] = mats[nums[l]]);
		}
		int mid = (l + r) / 2;
		build(x * 2, l, mid);
		build(x * 2 + 1, mid + 1, r);
		tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
	}

	void update(int x, int l, int r, int i, pair<matblock, matblock>& v)
	{
		if (l == r) return void(tree[x] = v);
		int mid = (l + r) / 2;
		if (i <= mid) update(x * 2, l, mid, i, v);
		else update(x * 2 + 1, mid + 1, r, i, v);
		tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
	}
};

signed main()
{
	fast();

#if 0&&_LOCAL
	ifstream in("e:/in.txt");
	cin.rdbuf(in.rdbuf());
#endif

	rep(i, matsz) unit.first.mat[i][i] = 1;

	rep(v, maxv)
	{
		matblock el;
		rep(i, maxv + 1) el.mat[i][i] += 1;

		el.mat[v][maxv] += -1;
		el.mat[maxv][maxv] += 1;
		el.mat[v][v] -= 1;
		el.mat[maxv][v] += 1;
		mats[v].first = el;

		matblock add;
		rep(i, maxv + 1) add.mat[i][v]++;
		rep(i, maxv + 1) add.mat[i][maxv]++;
		add.mat[v][v]--;
		add.mat[v][maxv]--;
		mats[v].second = add;
	}

	int n, q;
	cin >> n >> q;
	nums.resize(n);
	rep(i, n) cin >> nums[i];

	Tree tree(n);

	cout << tree.tree[1].first.mat[maxv][maxv] << "\n";

	while (q--)
	{
		int i, v;
		cin >> i >> v;
		i--;
		nums[i] = v;
		tree.update(1, 0, n - 1, i, mats[nums[i]]);
		cout << tree.tree[1].first.mat[maxv][maxv] << "\n";
	}

	return 0;
}
