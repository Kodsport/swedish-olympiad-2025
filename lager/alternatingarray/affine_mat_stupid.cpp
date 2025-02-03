// proof of concept for matrix multiplication. no segtree
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


const int blocksize = 850;

const int numblocks = (int(1e5) + blocksize - 1) / blocksize;
ull blocks[numblocks][maxv + 1][maxv + 1];

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
pair<matblock, matblock> unit;
pair<matblock, matblock> mats[maxv];

pair<matblock, matblock> merge(pair<matblock, matblock>& a, pair<matblock, matblock>& b)
{
	matblock result;
	matblock transpose;
	rep(i, matsz) rep(j, matsz) transpose.mat[i][j] = a.first.mat[j][i] + a.second.mat[j][i];
	rep(i, matsz)
	{
		rep(j, matsz)
		{
			int t = 0;
#pragma GCC ivdep
			rep(k, matsz)
			{
				t += (a.first.mat[i][k]+a.second.mat[i][k]) * b.first.mat[k][j];
			}
			result.mat[i][j] = t;
		}
	}
	return make_pair(result, b.second);
}


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

	rep(i, maxv + 1) unit.first.mat[i][i] = 1;


	int n, q;
	cin >> n >> q;
	vector<ull> nums(n);
	rep(i, n) cin >> nums[i];

	auto solve = [&]()
		{
			pair<matblock, matblock> start;

			ull block[maxv + 1][maxv + 1];
			memset(block, 0, sizeof(block));

			rep(i, n)
			{
				int v = nums[i];

				
				start = merge(start, mats[v]);


				rep(j, maxv + 1)
				{
					ull val = 1 + block[j][maxv] - block[j][v];
					block[j][v] += val;
					block[j][maxv] += val;
				}
				block[v][v]--;
				block[v][maxv]--;

				rep(i, maxv + 1)
				{
					rep(j, maxv + 1)
					{
						cout << block[i][j] << " ";
					}
					cout << "\n";
				}
				cout << "\n";
				rep(i, maxv + 1)
				{
					rep(j, maxv + 1)
					{
						cout << start.first.mat[i][j]+start.second.mat[i][j] << " ";
					}
					cout << "\n";
				}
				cout << "*****\n";
			}
			cout << 2 + start.first.mat[maxv][maxv];
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
