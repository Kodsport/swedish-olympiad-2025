// #pragma GCC target ("avx,avx2,fma")
// #pragma GCC optimize ("Ofast,inline") // O1 - O2 - O3 - Os - Ofast
// #pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (ll i = (a); i < (b); ++i)
#define per(i, a, b) for (ll i = (b) - 1; i >= (a); --i)
#define trav(a, x) for (auto &a : x)

#define all(x) x.begin(), x.end()
#define sz(x) (ll)x.size()
#define pb push_back
#define debug(x) cout<<#x<<" = "<<x<<endl

#define umap unordered_map
#define uset unordered_set

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<ll,pll> ppll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<vll> vvll;

const ll INF = 1'000'000'007;

vll degrees;
vector<vvll> graph;
vvll dists;
vll best_dists;


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n,m;
    cin>>n>>m;
    graph.resize(n);
    dists.resize(n);
    degrees.assign(n,0);
    best_dists.assign(n,INF);
    rep(i,0,m) {
        ll res,k;
        cin>>res>>k;
        ll edgeid=sz(dists[res]);
        dists[res].pb(0);
        rep(j,0,k) {
            ll coef,f;
            cin>>coef>>f;
            graph[f].pb({coef,res,edgeid});
        }
        degrees[res]+=k;
    }
    
    queue<ll> q;
    rep(i,0,n) if(!degrees[i]) q.push(i);
    ll cnt=0;
    best_dists[0]=1;
    while(sz(q)) {
        ll f=q.front(); q.pop();
        ++cnt;
        trav(dist,dists[f]) best_dists[f]=min(best_dists[f],dist);
        trav(edge,graph[f]) {
            ll coef=edge[0],res=edge[1],edgeid=edge[2];
            dists[res][edgeid]+=coef*best_dists[f];
            --degrees[res];
            if(!degrees[res]) q.push(res);
        }
    }
    assert(cnt==n);
    cout<<best_dists[n-1]<<endl;
    return 0;
}