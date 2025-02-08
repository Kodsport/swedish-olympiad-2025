#include <bits/stdc++.h>
using namespace std;


#define ll long long
#define INF ((ll)(1e9+7))
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

vvpl adj(100001);
vvpl bl(22, vpl(100001, {0, 0}));
vl depth(100001, 0);

void dfs(ll u, ll last = -1, ll d = 0){
    depth[u] = d;
    for(auto &[v, w] : adj[u]){
        if(v == last) continue;
        bl[0][v] = {u, w};
        dfs(v, u, d+1);
    }
}

ll lcaDistance(ll u, ll v){
    ll res = 0;
    if(depth[u] < depth[v]) swap(u, v);
    for(ll i = 21; i >= 0; i--){
        if(depth[bl[i][u].F] >= depth[v]){
            res += bl[i][u].S;
            u = bl[i][u].F;
        }
    }
    for(ll i = 21; i >= 0; i--){
        if(bl[i][u].F != bl[i][v].F){
            res += bl[i][u].S+bl[i][v].S;
            u = bl[i][u].F;
            v = bl[i][v].F;
        }
    }
    if(u != v){
        res += bl[0][u].S+bl[0][v].S;
    }
    return res;
}

int main() { // kan få 10p mer men orka
    
    cin.tie(0)->sync_with_stdio(0);

    ll n, k, from, to, t, d, weight;
    cin >> n >> k;

    fo(i, n-1){
        cin >> from >> to >> weight;
        adj[--from].pb({--to, weight});
        adj[to].pb({from, weight});
    }

    dfs(0);

    fo(i, 21){
        fo(j, n){
            bl[i+1][j].F = bl[i][bl[i][j].F].F;
            bl[i+1][j].S = bl[i][j].S+bl[i][bl[i][j].F].S;
        }
    }

    vector<tuple<ll, ll, ll, ll>> queries;
    fo(i, k){
        cin >> from >> to >> t >> d;
        --from; --to;
        queries.pb({t, d, from, to});
    }

    sort(rall(queries));
    vector<tuple<ll, ll, ll>> tag;

    ll from2, t2, score;
    for(auto &[t, d, from, to] : queries){
        ll res = 1;
        fo(i, tag.size()){
            tie(t2, from2, score) = tag[i];
            ll dis = lcaDistance(to, from2);
            // deb(dis);
            if(dis+d+t <= t2){
                res = max(res, score+1);
            }
        }
        // deb(res);
        tag.pb({t, from, res});
    }
    
    fo(i, n){
        ll res = 0;
        fo(j, tag.size()){
            tie(t2, from2, score) = tag[j];
            ll dis = lcaDistance(i, from2);
            if(dis <= t2){
                res = max(res, score);
            }
        }
        cout << res << " ";
    }
 

    return 0;
}