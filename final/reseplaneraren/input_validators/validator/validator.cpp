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

struct UF {
	vector<int> v;
	UF(int n) : v(n, -1) {}
	int find(int x) { return v[x] < 0 ? x : v[x] = find(v[x]); }
	bool join(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;
		if (-v[a] < -v[b]) swap(a, b);
		v[a] += v[b];
		v[b] = a;
		return true;
	}
};

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

const int MAXN = 300005;
vi depth(MAXN,-1);
vector<vi> g(MAXN, vi());

void dfs2(int cur, int par) {
    if (par != -1) 
        depth[cur] = depth[par] + 1;
    
    for (int &nei:g[cur]) 
        if (nei != par) dfs2(nei,cur);
    
}

struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	int dist(int a,int b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

void run() {
    string mode = Arg("mode", "none");

    

    int n = Int(1, Arg("maxn"));
    Space();
    int k = Int(1, Arg("maxk"));
    Space();
    int q = Int(1, Arg("maxq"));
    Endl();

    UF uf(n);
    rep(i,0,n-1)
    {
        int a = Int(1,n);
        Space();
        int b = Int(1,n);
        Endl();
        a--; b--;
        assert(uf.join(a,b));
        g[a].push_back(b);
        g[b].push_back(a);
    }

    depth[0] = 0;
    dfs2(0,-1);

    rep(i,0,k)
    {
        int a = Int(1,n);
        Space();
        int b = Int(1,n);
        Endl();
        assert(a != b);
    }

    LCA lca(g);

    rep(i,0,q)
    {
        int a = Int(1,n);
        Space();
        int b = Int(1,n);
        Endl();
        assert(a != b);

        if (mode == "g4") assert(lca.dist(0,a-1) + lca.dist(a-1,b-1) == lca.dist(0,b-1));
    }


    Eof();
}

