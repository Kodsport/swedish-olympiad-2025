#include "validator.h"

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

vvll graph;
vll state;
bool has_cycle=0;

void dfs(ll u) {
    state[u]=1;
    trav(v,graph[u]) {
        if(state[v]==0) dfs(v);
        if(state[v]==1) has_cycle=1;
    }
    state[u]=2;
}

vpll trades;
vll trades_cost;
vector<vpll> items;

void run() {
    int n = Int(1, Arg("maxn"));
    Space();
    int m = Int(1, 100'000);
    Endl();
    ll K=0;
    graph.assign(n,vll());
    state.assign(n,0);

    ll maxki=ll(Arg("maxki"));
    items.assign(n,vpll());
    rep(i,0,m) {
        ll res = Int(0, n-1);
        Space();
        ll ki = Int(1, maxki); // set max to n for now, it is good enough
        K += ki;
        Endl();
        trades.emplace_back(res,ki);
        rep(j,0,ki) {
            ll coef = Int(1, 100);
            Space();
            ll item = Int(0, n-1);
            Endl();
            graph[item].pb(res);
            items[item].emplace_back(coef,i);
        }
    }
    assert(K<=ll(Arg("maxk")));

    ll acyclic = ll(Arg("acyclic"));
    if(acyclic) {
        rep(i,0,n) if(!state[i]) dfs(i);
        assert(has_cycle==0);
    }
    Eof();

    trades_cost.assign(m, 0);
    vll dists(n,INF);
    dists[0]=1;
    set<pll> pq;
    pq.emplace(1,0);
    while(!pq.empty()) {
        ll d,item;
        tie(d,item)=*pq.begin();
        pq.erase(pq.begin());
        trav(term,items[item]) {
            ll coef,trade;
            tie(coef,trade)=term;
            trades_cost[trade]+=coef*d;
            if(--trades[trade].second==0) {
                ll nitem=trades[trade].first;
                if(trades_cost[trade]<dists[nitem]) {
                    pq.erase({dists[nitem],nitem});
                    dists[nitem]=trades_cost[trade];
                    pq.emplace(dists[nitem],nitem);
                }
            }
        }
    }
    rep(i,0,n)  assert(trades_cost[i]<=1'000'000'000);
}
