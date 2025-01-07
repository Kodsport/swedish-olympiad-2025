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
    int n_is = Arg("n");
    int n = Int(n_is, n_is);
    Space();
    int k = Int(Arg("klo"), Arg("khi"));
    Endl();
    
    string s = Line();
    assert(sz(s) == n);
    for (char c : s)
    {
        assert(c >= 'a' && c <= 'a'+k-1);
    }

    Eof();
}

