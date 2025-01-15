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

vvl adj(500001);

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, from, to;
    cin >> n >> m;
    vl v(n);
    fo(i, n){
        cin >> v[i];
        if(v[i] == -1) v[i] = INF;
    }

    fo(i, m){
        cin >> from >> to;
        adj[--from].pb(--to);
        adj[to].pb(from);
    }
    vl ans(n, 0), seen(n);

    queue<tuple<ll, ll, ll>> q;
    q.push({0, 0, -1});
    ll pos, weight, last, res = 0;
    while(!q.empty()){
        tie(pos, weight, last) = q.front();
        q.pop();
        // deb(pos);
        // deb2(weight, v[pos]);
        if(v[pos]>weight && last != -1){
            if(!ans[last])res++;
            ans[last] = 1;
            // deb(pos);
            continue;
        }
        if(seen[pos]) continue;
        seen[pos] = 1;
        for(auto &v : adj[pos]){
            q.push({v, weight+1, pos});
        }
    }
    vl v2(n, INF);
    q.push({0, 0, -1});
    while(!q.empty()){
        tie(pos, weight, last) = q.front();
        q.pop();
        if(v2[pos] != INF) continue;
        v2[pos] = weight;
        if(ans[pos]) continue;
        for(auto &v : adj[pos]){
            q.push({v, weight+1, pos});
        }
    }
    fo(i, n){
        if(v2[i] != v[i]){
            cout << "-1";
            exit(0);
        }
    }
    cout << res << "\n";
    fo(i, n){
        if(ans[i]) cout << i+1 << " ";
    }
    

    return 0;
}