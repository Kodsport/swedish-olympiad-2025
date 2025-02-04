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

const ll MAXN = 300000;

void run() {
    ll n = Int(1, int(Arg("n", MAXN)));
    Space();
    ll m = Int(1, int(Arg("m", MAXN)));
    Space();
    ll q = Int(1, int(Arg("q", MAXN)));
    Endl();

    int start_x = -1;
    int start_y = -1;

    for(int c1 = 0; c1 < n; c1++){
        vi row = SpacedInts<int>(m, -1, MAXN);
        for(int c2 = 0; c2 < m; c2++){
            if(row[c2] == 0){
                assert(start_x == -1);
                start_x = c1;
                start_y = c2;
            }
        }
    }
    assert(start_x != -1);

    for(int c1 = 0; c1 < q; c1++){
        char ch = Char();
        if(ch == '?'){
            Space();
            Int(1, n);
            Space();
            Int(1, m);
            Endl();
        }
        else{
            assert(ch == '!');
            Space();
            int r = Int(1, n);
            Space();
            int c = Int(1, m);
            Space();
            int d = Int(-1,MAXN);
            Endl();
            r--;
            c--;
            

            assert(!(r == start_x && c == start_y));
            assert(d != 0);
        }
    }

    Eof();
}

