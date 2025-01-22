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
    bool iden = Arg("identity", 0);
    int maxt = Arg("t", 1000000000);

    int n = Int(2, int(Arg("n", 300000)));
    Endl();
    for(int c1 = 0; c1 < n; c1++){
        int t = Int(1, maxt);
        Endl();
        if(iden)assert(t == c1+1);
    }
    Eof();
}

