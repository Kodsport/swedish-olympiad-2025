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


void run() {

  
    int N = Int(2, 20000); Space();
    int Q = Int(1, 1000000000); Space();
    int T = Int(0, 6); Endl(); // check which testcase it is

    assert(T == (int) Arg("group")); // Chech it is the correct group 

    vi pos = SpacedInts(N,0,1000'000'000);
    
    if (T == 1) {
        assert(N == 2);
        assert(Q == 3);
    }
    else if (T == 2) {
        assert(Q == 2*N-1);
        
        sort(all(pos));
        rep(i,0,N-1) assert(pos[i] == pos[i+1]-1);
    }
    else if (T == 3) {
        assert(N <= 100);
        assert(Q == N*N + N);
    }
    else if (T == 4) {
        assert(N <= 100);
        assert(Q == 33*N);
    }
    else if (T == 5) {
        assert(N <= 1000);
        assert(Q == 2*N-1);
    }
    else if (T == 6) {
        assert(Q == 2*N-1);
    }

    Eof();
}

