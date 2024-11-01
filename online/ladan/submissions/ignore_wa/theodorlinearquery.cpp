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

vvl adj(300000);
vl lo(300000, -1), d(300000, -1), res(300000, 0), seen(300000, 0);
ll r, c, q;

void ArticulationPoints(int u, int last = -1, int depth = 0){
    lo[u] = depth;
    d[u] = depth;
    bool fail = 1;
    for(auto v : adj[u]){
        if(v == last) continue;
        if(d[v] != -1){
            lo[u] = min(lo[u], d[v]);
            continue;
        }
        ArticulationPoints(v, u, depth+1);
        lo[u] = min(lo[u], lo[v]);
        if(lo[v]>=depth) fail = 0;
    }
    if(!fail && last!=-1) res[u] = 1;
}

stack<pl> st;
ll currNum = 0, startPos, goalPos;
vvl connections(300000);

void BCC(int u, int last = -1){
    seen[u] = 1;
    for(auto &v : adj[u]){
        if(v == last) continue;
        if(seen[v]) continue;
        st.push({u, v});
        BCC(v, u);
        if(res[u] || last == -1){
            while(!st.empty()){
                pl temp = st.top();
                st.pop();
                if(connections[temp.F].empty() || connections[temp.F].back() != currNum) connections[temp.F].pb(currNum);
                if(connections[temp.S].empty() || connections[temp.S].back() != currNum) connections[temp.S].pb(currNum);
                if(temp == pl{u, v}) break;
            }
            currNum++;
        }
    }
}

ll dfs(int u){
    if(u == startPos) return u;
    seen[u] = 1;
    for(auto &v : adj[u]){
        if(seen[v]) continue;
        if(dfs(v)>=0) return v;
    }
    return -1;
}

unordered_set<ll> vis;
vpl dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
ll toIndex(ll row, ll col){
    return row*c+col;
}

bool dfs2(ll box, ll player){
    if(vis.count(box*((ll)1e9)+player)) return 0;
    vis.insert(box*((ll)1e9)+player);
    if(box == goalPos) return 1;

    for(auto &[a, b] : dirs){
        ll y = box/c+a;
        ll x = box%c+b;
        if(x<0 || y<0 || x>=c || y>=r) continue;
        ll nextPlayer = toIndex(y, x);
        if(nextPlayer == player) continue;
        for(auto &i : connections[player]){
            for(auto &j : connections[nextPlayer]){
                if(i == j){
                    if(dfs2(box, nextPlayer)) return 1;
                    break;
                }
            }
        }
    }
    ll y = (box/c)*2ll-player/c;
    ll x = (box%c)*2ll-player%c;
    if(x<0 || y<0 || x>=c || y>=r) return 0;
    ll nextPlayer = toIndex(y, x);
    if(adj[nextPlayer].size()==0) return 0;
    if(dfs2(nextPlayer, box)) return 1;

    return 0;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> r >> c >> q;
    vector<string> grid(r);
    fo(i, r){
        cin >> grid[i];
    }
    fo(i, r){
        fo(j, c){
            if(grid[i][j] == '#') continue;
            if(i<r-1 && grid[i+1][j] != '#'){
                adj[toIndex(i, j)].pb(toIndex(i+1, j));
                adj[toIndex(i+1, j)].pb(toIndex(i, j));
            }
            if(j<c-1 && grid[i][j+1] != '#'){
                adj[toIndex(i, j)].pb(toIndex(i, j+1));
                adj[toIndex(i, j+1)].pb(toIndex(i, j));
            }
        }
    }

    fo(i, r*c){
        if(lo[i] != -1) continue;
        ArticulationPoints(i);
    }
    lo.assign(300000, -1);
    for(ll i = r*c-1; i>=0; i--){
        if(lo[i] != -1) continue;
        ArticulationPoints(i);
    }

    fo(i, r*c){
        if(seen[i]) continue;
        BCC(i);
    }

    while(q--){
        ll xStart, yStart, xBox, yBox, xGoal, yGoal;
        cin >> yStart >> xStart >> yBox >> xBox >> yGoal >> xGoal;
        xStart--; yStart--; xBox--; yBox--; xGoal--; yGoal--;

        startPos = toIndex(yStart, xStart); 
        goalPos = toIndex(yGoal, xGoal); 
        seen.assign(300000, 0);
        ll starting = dfs(toIndex(yBox, xBox));
        if(starting == -1){
            cout << "Nej\n";
            continue;
        }
        vis.clear();
        cout << (dfs2(toIndex(yBox, xBox), starting)?"Ja":"Nej") << "\n";

    }

    return 0;
}