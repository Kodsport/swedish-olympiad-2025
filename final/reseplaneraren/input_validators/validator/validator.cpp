#include "validator.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct UF {
	vector<int> v;
	UF(int n) : v(n, -1) {}
	int find(int x) { return v[x] < 0 ? x : v[x] = find(v[x]); }
	bool join(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;
		if (-v[a] < -v[b]) swap(a, b);
		v[a] += v[b];
		v[b] = a;
		return true;
	}
};


void run() {
    int n = Int(1, Arg("maxn"));
    Space();
    int k = Int(1, Arg("maxk"));
    Space();
    int q = Int(1, Arg("maxq"));
    Endl();

    UF uf(n);
    rep(i,0,n-1)
    {
        int a = Int(1,n);
        Space();
        int b = Int(1,n);
        Endl();
        a--; b--;
        assert(uf.join(a,b));
    }

    rep(i,0,k)
    {
        int a = Int(1,n);
        Space();
        int b = Int(1,n);
        Endl();
        assert(a != b);
    }

    rep(i,0,q)
    {
        int a = Int(1,n);
        Space();
        int b = Int(1,n);
        Endl();
        assert(a != b);
    }


    Eof();
}

