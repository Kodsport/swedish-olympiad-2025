#include <bits/stdc++.h>
using namespace std;


#define ll long long
#define INF ((ll)(1e9))
#define fo(i, n) for(ll i=0;i<((ll)n);i++)
#define deb(x) cout << #x << " = " << (x) << endl;
#define deb2(x, y) cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define LSOne(S) ((S) & (-S))
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<vpii> vvpii;
typedef vector<vpl> vvpl;


struct BitSet {
    #define W 6
    #define mask 63
    #define get_size(n) ((n)<1?0:((n)+mask)>>W)
    typedef unsigned long long uint;

    uint* a;        
    int size;      
    int S;           

    BitSet(int bits) : S(bits), size(get_size(bits)) {
        a = new uint[size];
        reset();
    }

    BitSet(int bits, uint x) : S(bits), size(get_size(bits)) {
        a = new uint[size];
        reset();
        a[0] = x;
    }

    BitSet(const BitSet &x) : S(x.S), size(x.size) {
        a = new uint[size];
        std::memcpy(a, x.a, sizeof(uint) * size);
    }

    ~BitSet() {
        delete[] a;
    }

    void reset() {
        std::memset(a, 0, sizeof(uint) * size);
    }

    BitSet& set(int x, int y) {
        int X = x >> W, Y = x & mask;
        if (y) a[X] |= 1ull << Y;
        else a[X] &= ~(1ull << Y);
        return *this;
    }

    int find(int x) const {
        int X = x >> W, Y = x & mask;
        return (a[X] >> Y) & 1ull;
    }

    int operator [](int x) const {
        return find(x);
    }

    BitSet& operator=(const BitSet &y) {
        if (this != &y) {
            if (size != y.size) {
                delete[] a;
                size = y.size;
                a = new uint[size];
            }
            std::memcpy(a, y.a, sizeof(uint) * size);
            S = y.S;
        }
        return *this;
    }

    BitSet& operator|=(const BitSet &y) {
        if (size != y.size) throw std::invalid_argument("Size mismatch in operator|=");
        for (int i = 0; i < size; ++i) {
            a[i] |= y.a[i];
        }
        return *this;
    }

    void correction() {
        if (S & mask) a[size - 1] &= (1ull << (S & mask)) - 1;
    }

    #undef mask
    #undef W
    #undef get_size
};

unordered_map<ll, vl> adj2, adj2R; 
stack<pl> st;
ll startPos, goalPos;
vvl connections(300000);
vvl adj(100001);
vector<unordered_map<ll, ll>> adjPush(100001);


vl topo;
set<ll> vis;
vector<set<ll>> adjSCC;
void toposort(ll u, bool fir = 1){
    if(vis.count(u)) return;
    vis.insert(u);
    if(fir)for(auto &v : adj2[u]){
        toposort(v, fir);
    }else for(auto &v : adjSCC[u]){
        toposort(v, fir);
    }
    topo.pb(u);
}  

ll color = 1;
unordered_map<ll, ll> SCC;
void dfs(ll u){
    if(SCC.count(u)) return;
    SCC[u] = color;
    for(auto &v : adj2R[u]){
        dfs(v);
    }
}  



struct UnionFind{
    ll n;
    vl siz, p;
    vector<pair<pl, pl>> prev;
    UnionFind(int N) : n(N){
        p.resize(n);
        siz.resize(n, 1);
        fo(i, n) p[i] = i;
    }
    bool same(int a, int b){
        return find(a) == find(b);
    }

    int find(int x){
        if (x == p[x]) return x;
        return find(p[x]);
    }

    void unite(int a, int b){
        a = find(a);
        b = find(b);
        prev.pb({{-1, -1}, {-1, -1}});
        if(a == b) return;
        if(siz[a] < siz[b]) swap(a, b);
        prev.back() = {{a, siz[a]}, {b, p[b]}};
        siz[a] += siz[b];
        p[b] = a;
    }

    void rollback(){
        pl aa, bb;
        tie(aa, bb) = prev.back();
        prev.pop_back();
        if(aa.F !=-1){
            siz[aa.F] = aa.S;
            p[bb.F] = bb.S;
        }
    }
};

UnionFind dynamicConnectivity(300000);
vector<map<ll, bool>> connectedRes(300000);
vvpl toQuery(300000);


struct Node{
    Node *lnode, *rnode;
    vl elements;
    ll l, r;
    Node(ll l, ll r) : l(l), r(r) {
        if(r-l>1){
            ll mid = (r+l) / 2ll;
            lnode = new Node(l, mid);
            rnode = new Node(mid, r);
        }
    }

    void update(ll lo, ll hi, ll x){
        if(r <= lo || hi <= l) return;
        if(r <= hi && lo <= l){
            elements.pb(x);
            return;
        }
        lnode->update(lo, hi, x);
        rnode->update(lo, hi, x);
    }

    void walk(){
        for(auto &ed : elements) dynamicConnectivity.unite(ed/INF, ed%INF);
        if(r-l == 1){
            for(auto &[from, to] : toQuery[l]){
                connectedRes[l][from*INF+to] = dynamicConnectivity.same(from, to);
                connectedRes[l][to*INF+from] = dynamicConnectivity.same(to, from);
            }
            // titta också alla grannar till l
        }else{
            lnode->walk();
            rnode->walk();
        }
        fo(_, elements.size()) dynamicConnectivity.rollback();
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, m, q, from, to, nexta, nextb;
    cin >> n >> m >> q;
    vector<string> grid(n);
    UnionFind uf(n);
    fo(i, m){
        cin >> from >> to >> nexta >> nextb;
        from--; to--; nexta--; nextb--;
        adj[from].pb(to);
        adj[to].pb(from);
        adjPush[from][to] = nexta; // kanske tvärt om
        adjPush[to][from] = nextb;
        uf.unite(from, to);
    }


    vl allNodes;

    Node st(0, n);

    ll s, r, g;
    vector<tuple<ll, ll, ll>> que;
    fo(i, q){
        cin >> s >> r >> g;
        s--; r--; g--;
        que.pb({s, r, g});

        for(auto &ver : adj[r]){
            toQuery[r].pb({s, ver});
            // toQuery[r].pb({ver, s});
        }
    }

    fo(box, n){
        for(auto &player : adj[box]){
            for(auto &next : adj[box]){
                if(next == player) continue;
                toQuery[box].pb({player, next});
            }
        }
    }

    fo(i, n){
        for(auto &next : adj[i]){
            if(i>next) continue;
            st.update(0, i, i*INF+next);
            st.update(i+1, next, i*INF+next);
            st.update(next+1, n, i*INF+next);
            st.update(0, i, next*INF+i);
            st.update(i+1, next, next*INF+i);
            st.update(next+1, n, next*INF+i);
        }
    }

    st.walk();

    fo(box, n){
        for(auto &ver : adj[box]){
            ll player = ver;
            allNodes.pb(box*((ll)1e9)+player);
            for(auto &ver2 : adj[box]){
                ll nextPlayer = ver2;
                if(nextPlayer == player) continue;
                if(connectedRes[box][nextPlayer*INF+player]){
                    adj2[box*((ll)1e9)+player].pb(box*((ll)1e9)+nextPlayer);
                    adj2R[box*((ll)1e9)+nextPlayer].pb(box*((ll)1e9)+player);
                }
            }
            ll nextPlayer = adjPush[player][box];
            
            adj2[box*((ll)1e9)+player].pb(nextPlayer*((ll)1e9)+box);
            adj2R[nextPlayer*((ll)1e9)+box].pb(box*((ll)1e9)+player);
        }
    }

    for(ll pos : allNodes){
        toposort(pos);
    }
    reverse(all(topo));

    fo(i, topo.size()){
        ll u = topo[i];
        if(SCC.count(u)) continue;
        dfs(u);
        ++color;
    }

    vector<BitSet> bs(color, (color)); 
    fo(i, color)bs[i].set(i, 1);

    adjSCC.resize(color);

    fo(i, topo.size()){
        ll u = topo[i];
        for(auto &v : adj2[u]){
            if(SCC[v] == SCC[u]) continue;
            adjSCC[SCC[u]].insert(SCC[v]);
        }
    }

    vl seen2(color+1, 0);
    fo(i, color){
        ll u = color-1-i;
        if(seen2[u]) continue;
        seen2[u] = 1;
        for(auto &v : adjSCC[u]){
            bs[u] |= bs[v];
        }
    }


    fo(i, q){
        tie(s, r, g) = que[i];
        if(!uf.same(r, s)){
            cout << "0\n";
            continue;
        }

        ll starting = -1;
        for(auto &ver : adj[r]){
            if(connectedRes[r][s*INF+ver]){
                starting = ver;
                break;
            }
        }
        
        bool possible = 0;
        for(auto &ver : adj[g]){
            // deb(ver);
            // // if(!connectedRes[g][starting*INF+ver]) continue;
            // deb(1);
            // if(SCC[r*((ll)1e9)+starting] == 0 || SCC[g*((ll)1e9)+ver] == 0) continue;
            if(bs[SCC[r*((ll)1e9)+starting]][SCC[g*((ll)1e9)+ver]]){
                possible = 1;
                break;
            }
        }
        cout << (possible?"1":"0") << "\n";
    }

    return 0;
}