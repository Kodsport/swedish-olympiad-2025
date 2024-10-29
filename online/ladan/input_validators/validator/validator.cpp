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
    int maxr = Arg("maxr");
    int r = Int(1, maxr);
    Space();
    int c = Int(1, maxr);
    Space();
    int q = Int(1, Arg("maxq"));
    Endl();

    fo(i, r)
    {
        Line();
    }

    pii first_box, first_goal;
    bool same_boxgoal = (int)Arg("sameboxgoal", 0);
    bool same_goal = (int)Arg("samegoal", 0);
    fo(i, q)
    {
        pii start;
        start.first = Int(1, r);
        Space();
        start.second = Int(1, c);
        Space();
        pii box;
        box.first = Int(1, r);
        Space();
        box.second = Int(1, c);
        Space();
        pii goal;
        goal.first = Int(1, r);
        Space();
        goal.second = Int(1, c);
        Endl();
        box.first--,box.second--,start.first--,start.second--,goal.first--,goal.second--;
        assert(start!=box&&box!=goal&&start!=goal);
        if (i==0)
        {
            first_box = box;
            first_goal = goal;
        }
        if (same_boxgoal)
        {
            assert(box==first_box);
            assert(goal==first_goal);
        }
        if (same_goal) assert(goal==first_goal);
    }

    Eof();
}

