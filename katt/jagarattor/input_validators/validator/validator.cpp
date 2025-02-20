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
    int m = Int(1, Arg("maxm"));
    Space();
    int q = Int(1, Arg("maxq"));
    Endl();

    int maxdeg = Arg("maxdeg", n);

    set<pii> edges;
    vi deg(n);
    vector<pii> rat_escapes;
    rep(i,0,m)
    {
        int u = Int(1,n);
        Space();
        int v = Int(1,n);
        Space();
        int a = Int(1,n);
        Space();
        int b = Int(1,n);
        Endl();

        u--; v--; a--; b--;
        assert(u!=v);
        pii p = {u,v};
        assert(edges.count(p)==0);
        edges.emplace(u,v);
        edges.emplace(v,u);
        rat_escapes.emplace_back(v,a);
        rat_escapes.emplace_back(u,b);

        deg[u]++;
        deg[v]++;
        assert(deg[u]<=maxdeg);
        assert(deg[v]<=maxdeg);
    }

    for (auto e : rat_escapes) assert(edges.count(e));


    int first_rat, first_goal;
    bool same_boxgoal = (int)Arg("sameboxgoal", 0);
    bool same_goal = (int)Arg("samegoal", 0);
    fo(i, q)
    {
        int s = Int(1,n);
        Space();
        int r = Int(1,n);
        Space();
        int t = Int(1,n);
        Endl();

        s--; r--; t--;
        assert(s!=r&&r!=t&&t!=s);

        // if (i==0)
        // {
        //     first_box = box;
        //     first_goal = goal;
        // }
        // if (same_boxgoal)
        // {
        //     assert(box==first_box);
        //     assert(goal==first_goal);
        // }
        // if (same_goal) assert(goal==first_goal);
    }

    Eof();
}

