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
	int n = Int(1, Arg("maxn"));
	Endl();
	ll maxe = Arg("maxe");
	SpacedInts(n, 1ll, maxe);
}
