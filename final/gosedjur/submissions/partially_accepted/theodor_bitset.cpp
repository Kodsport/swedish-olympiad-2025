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

vector<set<ll>> adj(1000001);
vector<bitset<20001>> bs;
vl seen, impossible;

void dfs(ll u){
    if(seen[u] == 1) impossible[u] = 1;
    if(seen[u]) return;
    seen[u] = 1;
    for(auto &v : adj[u]){
        dfs(v);
        impossible[u]|=impossible[v];
        bs[u]|=bs[v];
    }
    seen[u] = 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, r, c;
    cin >> n >> r >> c;
    vvl grid(r, vl(c));
    fo(i, r){
        fo(j, c){
            cin >> grid[i][j];
            if(i && grid[i][j] != grid[i-1][j]){
                adj[grid[i][j]-1].insert(grid[i-1][j]-1);
            }
        }
    }
    seen.assign(n, 0);
    impossible.assign(n, 0);

    fo(i, n){
        bitset<20001> temp;
        temp[i] = 1;
        bs.pb(temp);
    }

    fo(i, n){
        if(!seen[i]) dfs(i);
        if(impossible[i]) cout << "-1 ";
        else cout << bs[i].count()-1 << " ";
    }



    return 0;
}