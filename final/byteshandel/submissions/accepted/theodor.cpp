#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define fo(i, n) for(ll i=0;i<((ll)n);i++)
typedef vector<ll> vl;

int main() {
    cin.tie(0)->sync_with_stdio(0);


    ll n, m, r, k, c, t;
    cin >> n >> m;
    vl cost(m, 0), dest(m), am(m), res(n, 0);
    vector<vector<pair<ll,ll>>> adj(n);
    fo(i, m){
        cin >> r >> k;
        dest[i] = r;
        am[i] = k;
        fo(j, k){
            cin >> c >> t;
            adj[t].push_back({i, c});
        }
    }

    priority_queue<pair<ll,ll>> pq;
    pq.push({-1, 0});
    ll co, pos;
    while(!pq.empty()){
        tie(co, pos) = pq.top();
        co = -co;
        pq.pop();
        if(res[pos]) continue;
        res[pos] = co;
        for(auto &[ind, w] : adj[pos]){
            am[ind]--;
            cost[ind]+=w*res[pos];
            if(!am[ind]){
                pq.push({-cost[ind], dest[ind]});
            }
        }
    }
    cout << res[n-1];

    return 0;
}