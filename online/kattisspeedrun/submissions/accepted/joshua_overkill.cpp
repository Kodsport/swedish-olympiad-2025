// The techniques used in this solution are overkill and are COMPLETELY irrelevant to Programmeringsolympiaden 
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


typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8;
#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j

struct LPSolver {
	int m, n;
	vi N, B;
	vvd D;

	LPSolver(const vvd& A, const vd& b, const vd& c) :
		m(sz(b)), n(sz(c)), N(n + 1), B(m), D(m + 2, vd(n + 2)) {
		repp(i, 0, m) repp(j, 0, n) D[i][j] = A[i][j];
		repp(i, 0, m) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
		repp(j, 0, n) { N[j] = j; D[m][j] = -c[j]; }
		N[n] = -1; D[m + 1][n] = 1;
	}

	void pivot(int r, int s) {
		T* a = D[r].data(), inv = 1 / a[s];
		repp(i, 0, m + 2) if (i != r && abs(D[i][s]) > eps) {
			T* b = D[i].data(), inv2 = b[s] * inv;
			repp(j, 0, n + 2) b[j] -= a[j] * inv2;
			b[s] = a[s] * inv2;
		}
		repp(j, 0, n + 2) if (j != s) D[r][j] *= inv;
		repp(i, 0, m + 2) if (i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(int phase) {
		int x = m + phase - 1;
		for (;;) {
			int s = -1;
			repp(j, 0, n + 1) if (N[j] != -phase) ltj(D[x]);
			if (D[x][s] >= -eps) return true;
			int r = -1;
			repp(i, 0, m) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || MP(D[i][n + 1] / D[i][s], B[i])
					< MP(D[r][n + 1] / D[r][s], B[r])) r = i;
			}
			if (r == -1) return false;
			pivot(r, s);
		}
	}

	T solve(vd& x) {
		int r = 0;
		repp(i, 1, m) if (D[i][n + 1] < D[r][n + 1]) r = i;
		if (D[r][n + 1] < -eps) {
			pivot(r, n);
			if (!simplex(2) || D[m + 1][n + 1] < -eps) return -inf;
			repp(i, 0, m) if (B[i] == -1) {
				int s = 0;
				repp(j, 1, n + 1) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		repp(i, 0, m) if (B[i] < n) x[B[i]] = D[i][n + 1];
		return ok ? D[m][n + 1] : inf;
	}
};

// ILP. Maximize
bool is_integer(double x)
{
	return abs(x - floor(x)) < 1e-9;
}

int s, p, a, b;
double global_lb = -inf;
void bb(int d, vvd& A, vd& b, vd& c, vi& integer_constraint)
{
	if (d > 200)
	{
		return;
	}

	LPSolver simplex(A, b, c);
	vd x(sz(c));
	double v = simplex.solve(x);
	if (v == -inf) return;
	if (v < global_lb)
	{
		return;
	}
	assert(v != inf);
	bool any_violated = 0;

	rep(v, sz(c))
	{
		if (integer_constraint[v] && !is_integer(x[v]))
		{
			any_violated = 1;
			// test v <= floor(x[v])
			vd new_integrality(sz(c));
			new_integrality[v] = 1;

			b.push_back(floor(x[v]));
			A.push_back(new_integrality);
			bb(d + 1, A, b, c, integer_constraint);
			b.pop_back();
			A.pop_back();

			// test v >= ceil(x[v])
			new_integrality[v] = -1;
			b.push_back(-ceil(x[v]));
			A.push_back(new_integrality);
			bb(d + 1, A, b, c, integer_constraint);
			b.pop_back();
			A.pop_back();
		}
	}
	if (!any_violated)
	{
		global_lb = max(global_lb, v);
	}
}

signed main()
{
	fast();

	cin >> s >> p >> a >> b;

	vd c = { -a + 0.,-b + 0. };

	vvd A;
	A.push_back({ -1, -0.5 });
	vd b = { s - 0.5 * p - 1e-6 };
	vi integer_constraint(2, 1);


	bb(0, A, b, c, integer_constraint);
	cout << -global_lb;

	return 0;
}
