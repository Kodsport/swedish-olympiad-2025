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



int main() {
    cin.tie(0)->sync_with_stdio(0);


    ll n, m, r, k, c, t;
    cin >> n >> m;
    vl cost(m, 0), dest(m), am(m), res(n, 0);
    vvpl adj(n);
    fo(i, m){
        cin >> r >> k;
        dest[i] = r;
        am[i] = k;
        fo(j, k){
            cin >> c >> t;
            adj[t].pb({i, c});
        }
    }

    priority_queue<pl> pq;
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