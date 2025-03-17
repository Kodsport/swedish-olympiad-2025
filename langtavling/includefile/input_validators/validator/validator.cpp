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

	int maxk = Arg("maxk", 1000000000);
	int minN = Arg("minN", 1);
	int maxN = Arg("maxN", 1000000);
	int maxQ = Arg("maxQ", int(1e5));

	ll N = Int(minN, maxN); Space();
	ll k = Int(1, maxk); Space();
	ll Q = Int(1, maxQ); Endl();


	int minInc = Arg("minInc", 0);
	int maxInc = Arg("maxInc", N);

	ll incs = 0;
	rep(i,0,N) {
		string line = Line();
		assert(line.size() <= 35);
		for (char c : line) assert(isprint(c));
		if (line == "#include \"main.hpp\"") incs++;
	}

	assert(minInc <= incs && incs <= maxInc), "not the correct amount of #include \"main.hpp\"";

	__int128_t maxQueryVal = 1e12;
	__int128_t currLines = 0;
	rep(i,0,k) {
		currLines += (__int128_t) powl(incs,i)* (__int128_t)(N-incs);
		
		if (currLines >= maxQueryVal){
			currLines = maxQueryVal;
			break;
		}
	}	
	if (powl(incs,k) > maxQueryVal) currLines = maxQueryVal;
	if (currLines < maxQueryVal) currLines += (__int128_t) powl(incs, k);
	if (currLines < maxQueryVal) currLines *= incs;
	if (currLines < maxQueryVal) currLines += N-incs;

	rep(i,0,Q) {
		ll query = Int(1,(ll) min(maxQueryVal, currLines));
		Endl();
	}

	Eof();
}
