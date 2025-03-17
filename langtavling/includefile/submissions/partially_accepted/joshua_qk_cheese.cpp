// CHEESE: unconditionally correct if q*k < 10^8
// O(q(k+log(p)*log(n)))
// every time we don't go leftmost, we effectively compute our position mod nodesize[layer]
// when we mod, we either don't change or divide by 2. so we have log(N)*N. more careful analysis probably gives larger log base
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const int BIG = int(3e18 + 20);

inline bool isproductbig(long long num1, long long num2) {
	if (num1 == 0 || num2 == 0)
		return false;

	if (num1 > std::numeric_limits<long long>::max() / num2)
		return true;

	return num1 * num2 > 3e18;
}

struct bigint
{
	int v;
	bigint(int x) : v(x) {}
	bigint() : v(0) {}

	bigint operator+(const bigint& other)
	{
		if (v + other.v >= BIG) return bigint(BIG);
		return bigint(v + other.v);
	}

	bigint operator*(const bigint& other)
	{
		if (isproductbig(v, other.v)) return bigint(BIG);
		return bigint(v * other.v);
	}
};


string include = "#include \"main.hpp\"";

vector<bigint> nodesize;

vi isfile;
vector<string> lines;
vi includelines;
void walk(int layer, int pos)
{
	if (pos < includelines[0] || layer == -1)
	{
		cout << lines[pos] << "\n";
		return;
	}
	if (pos - includelines[0] < nodesize[layer].v)
	{
		walk(layer - 1, pos - includelines[0]);
		return;
	}

	auto getprev = [&](int mid)
		{
			if (mid == 0) return 0LL;
			return includelines[mid - 1];
		};

	// binary search for: prefix of includefiles we can eat
	int lo = -1;
	int hi = sz(includelines);
	while (lo + 1 < hi)
	{
		int mid = (lo + hi) / 2;

		int p = pos - includelines[mid] + mid - mid * nodesize[layer].v;

		if (p < (nodesize[layer]).v)
		{
			hi = mid;
		}
		else lo = mid;
	}

	if (hi==sz(includelines))
	{
		int p = pos - includelines.back() + hi - hi * nodesize[layer].v;
		cout << lines[includelines.back() + p] << "\n";
		return;
	}

	int p = pos - includelines[hi] + hi - hi * nodesize[layer].v;
	int middlepart = (includelines[hi] - getprev(hi));
	int pp = p + middlepart;
	if (pp < middlepart)
	{
		cout << lines[getprev(hi) + pp] << "\n";
		return;
	}
	else if (p < nodesize[layer].v)
	{
		walk(layer - 1, p);
		return;
	}
	assert(0);
}

signed main()
{
	fast();

	int n, k, q;
	cin >> n >> k >> q;
	cin.ignore();
	lines.resize(n);
	repe(l, lines) getline(cin, l);

	rep(i, n)
	{
		if (lines[i] == include) includelines.push_back(i);
	}

	int numinclude = 0;
	rep(i, n) numinclude += lines[i] == include;

	if (numinclude == 0)
	{
		while (q--)
		{
			int p;
			cin >> p;
			p--;
			cout << lines[p] << "\n";
		}
		return 0;
	}

	nodesize.push_back(n);
	vector<bigint> nodenuminclude;

	nodenuminclude.push_back(numinclude);

	while (sz(nodesize) < k + 5)
	{
		nodesize.push_back(nodesize.back() + nodenuminclude.back() * (n - 1));
		nodenuminclude.push_back(nodenuminclude.back() * numinclude);
	}

	int maxdepth = 0;
	while (maxdepth * q < int(1e8)) maxdepth++;

	while (q--)
	{
		// think of it as tree. every #include file is edge
		// make a walk in the tree
		// depth k
		// how big is a node? simple formula. all nodes will have same shape. binary search which one
		// HLD?
		// for big k: how many times will we not go leftmost?
		int p;
		cin >> p;
		p--;
		walk(min(k - 1, maxdepth), p);
	}

	return 0;
}
