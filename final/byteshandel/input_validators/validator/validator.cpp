#include "validator.h"

// #pragma GCC target ("avx,avx2,fma")
// #pragma GCC optimize ("Ofast,inline") // O1 - O2 - O3 - Os - Ofast
// #pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (ll i = (a); i < (b); ++i)
#define per(i, a, b) for (ll i = (b) - 1; i >= (a); --i)
#define trav(a, x) for (auto &a : x)

#define all(x) x.begin(), x.end()
#define sz(x) (ll)x.size()
#define pb push_back
#define debug(x) cout<<#x<<" = "<<x<<endl

#define umap unordered_map
#define uset unordered_set

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<ll,pll> ppll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<vll> vvll;

const ll INF = 1'000'000'007;

void run() {
    int n = Int(1, Arg("maxn"));
    Space();
    int m = Int(1, 100'000);
    Endl();
    ll K=0;
    rep(i,0,m) {
        ll res = Int(0, n-1);
        Space();
        ll ki = Int(1, n); // set max to n for now, it is good enough
        K += ki;
        Endl();
        rep(j,0,ki) {
            ll coef = Int(1, 100);
            Space();
            ll item = Int(0, n-1);
            Endl();
        }
    }
    assert(K<=ll(Arg("maxk")));
    Eof();
}