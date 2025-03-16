#include <bits/stdc++.h>
#include "validator.h"

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void run() {

	int maxN = Arg("maxN", 500000);
	int diff = Arg("diff", 500000);

	ll N = Int(1, maxN); Space();
	ll E = Int(0, 1e9); Endl();

	vector<int> a = SpacedInts(N, 1, (int) 1e9);
	set<int> unique;
	rep(i,0,N) unique.insert(a[i]);
	
	assert(sz(unique) <= diff);

	Eof();
}
