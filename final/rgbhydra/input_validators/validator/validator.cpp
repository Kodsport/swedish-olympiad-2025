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
    ll R = Int(0,Arg("R_max", 1e18)); Space();
    ll G = Int(0,Arg("G_max", 1e18)); Space();
    ll B = Int(0,Arg("B_max", 1e18)); Space();
    ll k = Int(0,Arg("k_max", 1e18)); 
    Endl();

    assert(R+G+B > 0);

    if ((int) Arg("smallK",0) != 0) assert(k <= R && k <= G && k <= B);

    Eof();
}

