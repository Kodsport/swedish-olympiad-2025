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
    string a = Line();
    string b = Line();

    ll n=a.size();
    ll m=b.size();
    int maxlen = Arg("maxlen");
    assert(m<=n);
    assert(n >= 1 && n <= maxlen);
    assert(m >= 1 && m <= maxlen);
    ll max=Arg("maxdiff");

    if(max!=-1) assert(n-m<=max);
    
    bool unique=Arg("unique");
    if(unique) {
        vector<bool> counter(200,false);
        rep(i,0,n) {
            assert(counter[a[i]]==false);
            counter[a[i]]=true;
        }

        counter.assign(200,false);
        rep(i,0,n) {
            assert(counter[b[i]]==false);
            counter[b[i]]=true;
        }
    }

    Eof();
}

