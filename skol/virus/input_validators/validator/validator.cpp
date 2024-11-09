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
    string F = Line();
    string H = Line();

    ll n=H.size();
    ll m=F.size();
    int maxlen = Arg("maxlen");
    assert(m<=n);
    assert(n >= 1 && n <= maxlen);
    assert(m >= 1 && m <= maxlen);
    ll max=Arg("maxdiff");

    if(max!=-1) assert(n-m==max);

    bool unique=Arg("unique");
    if(unique) {
        vector<bool> seen(200,false);
        for (auto c : F) {
            assert(seen[c]==false);
            seen[c]=true;
        }

        seen.assign(200,false);
        for (auto c : H) {
            assert(seen[c]==false);
            seen[c]=true;
        }
    }

    Eof();
}

