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

ll n,m;
vpll trades;
vll trades_cost;
vector<vpll> items;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin>>n>>m;
    items.assign(n,vpll());
    rep(i,0,m) {
        ll res,k;
        cin>>res>>k;
        trades.emplace_back(res,k);
        rep(j,0,k) {
            ll coef,item;
            cin>>coef>>item;
            items[item].emplace_back(coef,i);
        }
    }

    trades_cost.assign(m, 0);
    vll dists(n,INF);
    dists[0]=1;
    set<pll> pq;
    pq.emplace(1,0);
    while(!pq.empty()) {
        ll d,item;
        tie(d,item)=*pq.begin();
        if(item==n-1) break;
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

    cout<<dists[n-1]<<endl;
    return 0;
}