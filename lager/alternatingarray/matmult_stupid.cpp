// proof of concept for matrices. no segtree
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

	auto solve = [&]()
		{
			matblock start;
			rep(i, maxv + 1) start.mat[i][maxv + 1 + i] = 1;

			rep(i, n)
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
				start = start * el;


				/*rep(i, maxv + 1)
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
						cout << start.mat[i][j] << " ";
					}
					cout << "\n";
				}
				cout << "*****\n";*/
			}
			cout << 1 + start.mat[maxv][maxv];
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
