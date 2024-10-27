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
    int k_is = (int)Arg("k");
    int n_is = (int)Arg("n");
    int n = Int(n_is, n_is); Space();
    int k = Int(k_is, k_is); Endl();

    string message = Line();
    assert(sz(message)==n);
    int l = Int(0, n-1);
    Space();
    int r = Int(l, n-1);
    Endl();

    bool size1 = (bool)Arg("size1", 0);
    if (size1) assert(l==r);

    bool evenends = (bool)Arg("evenends", 0);
    if (evenends) assert(l%2==0&&r%2==0);

    bool lefteven = (bool)Arg("lefteven", 0);
    if (lefteven) assert(l%2==0);


    Eof();
}

