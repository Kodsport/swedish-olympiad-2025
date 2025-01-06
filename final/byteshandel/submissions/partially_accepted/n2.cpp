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
vector<vpll> trades;
vll trades_res;
vector<bool> used_trades;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin>>n>>m;
    trades.resize(m);
    rep(i,0,m) {
        ll res,k;
        cin>>res>>k;
        trades_res.pb(res);
        rep(j,0,k) {
            ll coef,item;
            cin>>coef>>item;
            trades[i].emplace_back(coef,item);
        }
    }

    used_trades.assign(m,0);
    vll dists(n,INF);
    dists[0]=1;
    while(true) {
        ll best_cost=INF,best_trade=-1;
        rep(i,0,m) {
            if(used_trades[i]) continue;
            ll cost=0;
            trav(term,trades[i]) {
                ll coef,item;
                tie(coef,item)=term;
                cost+=coef*dists[item];
            }
            if(cost<best_cost) {
                best_cost=cost;
                best_trade=i;
            }
        }
        if(best_trade==-1) break;
        ll res=trades_res[best_trade];
        used_trades[best_trade]=1;
        dists[res]=min(dists[res],best_cost);
    }

    cout<<dists[n-1]<<endl;
    return 0;
}