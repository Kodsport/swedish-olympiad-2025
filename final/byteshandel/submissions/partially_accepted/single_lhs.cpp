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

vector<vpll> graph;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n,m;
    cin>>n>>m;
    graph.assign(n,vpll());
    rep(i,0,m) {
        ll res,ki;
        cin>>res>>ki;
        assert(ki==1);
        ll coef,item;
        cin>>coef>>item;
        graph[item].emplace_back(res,coef);
    }

    vll dists(n,INF);
    set<pll> pq;
    pq.emplace(1,0);
    dists[0]=1;
    while(!pq.empty()) {
        ll d,u;
        tie(d,u)=*pq.begin();
        pq.erase(pq.begin());
        if(u==n-1) break;
        trav(edge,graph[u]) {
            ll v,w;
            tie(v,w)=edge;
            if(d*w>=dists[v]) continue;
            pq.erase({dists[v],v});
            dists[v]=d*w;
            pq.emplace(d*w,v);
        }
    }

    cout<<dists[n-1]<<endl;
    return 0;
}