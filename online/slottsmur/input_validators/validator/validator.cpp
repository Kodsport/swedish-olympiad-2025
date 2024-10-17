#include "validator.h"

#include <bits/stdc++.h>
using namespace std;

#define fo(i, n) for(ll i=0;i<((ll)n);i++)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;



void run() {
    int n = Int(1, Arg("maxn"));
    Space();
    int q = Int(1, Arg("maxq"));
    Endl();

    SpacedInts(n, 1, int(1e9));
    for (int i = 0; i < q; i++)
    {
        int t = Int(1,2);
        Space();
        if (t==1)
        {
            Int(1, n);
            Space();
            Int(1, int(1e9));
        }
        else
        {
            int l = Int(1, n);
            Space();
            Int(l, n);
        }
        Endl();
    }

    Eof();
}

