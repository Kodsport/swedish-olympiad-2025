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
    int n = Int(1, Arg("nmax", 1e5));
    Space();
    int m = Int(1, Arg("mmax", 1e5));
    Endl();

    ll sum = 0;
    ll max_duck = Arg("max_duck", 1e18);
    ll max_duck_sum = Arg("max_duck_sum", -1);
    fo(i, n){
        ll x = Int(0, max_duck);
        sum += x;
        if(max_duck_sum != -1) assert(sum <= max_duck_sum);
        if(i != n-1) Space();
    }
    Endl();
    bool c_is_i = Arg("c_is_i", 0);
    fo(i, m){
        if(c_is_i) Int(i+1, i+1);
        else Int(1, n);
        if(i != m-1) Space();
    }
    Endl();


    Eof();
}

