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

struct UF {
    vi e;
    UF(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
            a = find(a), b = find(b);
            if (a == b) return false;
            if (e[a] > e[b]) swap(a, b);
            e[a] += e[b]; e[b] = a;
            return true;
    }
};

void run() {
    int n = Int(1, Arg("maxn"));
    Space();
    int m = Int(1, Arg("maxm"));
    Space();
    int q = Int(1, Arg("maxq"));
    Endl();

    int maxdeg = Arg("maxdeg", n);

    UF uf(n);
    int numcomps = n;
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
        numcomps -= uf.join(u,v);

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
    assert(numcomps==1);

    for (auto e : rat_escapes) assert(edges.count(e));


    int first_rat, first_start, first_goal;
    bool samestart = (int)Arg("samestart", 0);
    bool samerat = (int)Arg("samerat", 0);
    bool samegoal = (int)Arg("samegoal", 0);
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

        if (i==0)
        {
            first_rat = r;
            first_start = s;
            first_goal = t;
        }
        if (samestart) assert(s==first_start);
        if (samerat) assert(r==first_rat);
        if (samegoal) assert(t==first_goal);
    }

    Eof();
}

