#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;

const int MAXN = 100001;
const ll nils = 1000000007;

int n,m,q;

vi val, comp, z, cont;
int Time, ncomps;
template<class G> int dfs(int j, G& g) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G> void scc(G& g) {
	int n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g);
}

vector<vi> DAG;
set<pii> edge_set;
vector<vi> D;

const int BSIZE = 200001;
vector<bitset<BSIZE> > reach;

void setup_scc(){
    scc(D);
    rep(c1,0,ncomps){
        vi temp;
        DAG.push_back(temp);
        bitset<BSIZE> bs;
        reach.push_back(bs);
    }
    rep(c1,0,sz(D)){
        trav(y, D[c1]){
            if(comp[y] != comp[c1] && edge_set.find({comp[c1],comp[y]}) == edge_set.end()){
                edge_set.insert({comp[c1],comp[y]});
                DAG[comp[c1]].push_back(comp[y]);
            }
        }
    }

    rep(c1,0,ncomps){
        reach[c1][c1] = 1;
        trav(y, DAG[c1]){
            reach[c1] |= reach[y];
        }
    }
}

bool can_reach(int i, int j){
    if(comp[i] == comp[j])return 1;
    int a = comp[i];
    int b = comp[j];
    return reach[a][b];
}

vi U,V,A,B;
vector<vi> CI(MAXN, vi());
map<pii,int> MI;

int chase(int from, int to){
    if(MI.find({from,to}) == MI.end())return to;
    int i = MI[{from,to}];
    if(from == U[i])return A[i];
    return B[i];
}

int nei(int u, int i){
    if(U[i] == u)return V[i];
    return U[i];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m >> q;
    rep(c1,0,m){
        int u,v,a,b;
        cin >> u >> v >> a >> b;
        u--;v--;a--;b--;
        U.push_back(u);
        V.push_back(v);
        A.push_back(a);
        B.push_back(b);
        MI[{u,v}] = c1;
        MI[{v,u}] = c1;
        CI[u].push_back(c1);
        CI[v].push_back(c1);
    }

    rep(c1,0,n*n){
        vi temp;
        D.push_back(temp);
    }

    rep(u,0,n){
        rep(v,0,n){
            if(u != v){
                int di = u*n+v;
                trav(i, CI[u]){
                    int u2 = nei(u,i);
                    int v2 = v;
                    if(u2 == v){
                        v2 = chase(u,v);
                    }
                    int dj = u2*n+v2;
                    D[di].push_back(dj);
                }

                D[di].push_back(v*n+v);
            }
        }
    }

    setup_scc();

    rep(c1,0,q){
        int s,r,t;
        cin >> s >> r >> t;
        s--;
        r--;
        t--;

        int di = s*n+r;
        int dj = t*n+t;
        cout << can_reach(di,dj) << "\n";
    }

    return 0;
}
