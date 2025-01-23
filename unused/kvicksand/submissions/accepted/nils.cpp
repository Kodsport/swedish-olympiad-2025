#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi BFS(vector<vi> &graph, vi &sand){
    vi D2(sz(graph), -1);
    vector<int> seen(sz(graph), 0);
    queue<int> Q;
    Q.push(0);
    D2[0] = 0;
    while(!Q.empty()){
        int a = Q.front();
        Q.pop();
        if(!seen[a]){
            seen[a] = 1;
            if(sand[a] == 0){
                for(auto b : graph[a]){
                    if(D2[b] == -1){
                        D2[b] = D2[a]+1;
                        Q.push(b);
                    }
                }
            }
        }
    }
    return D2;
}

vi solve(int n, int m, vi &D, vector<vi> &graph){
    vi sand(n, 0);
    vi sanded;
    rep(c1,0,n){
        trav(y, graph[c1]){
            if(D[c1] != -1 && (D[y] == -1 || D[y] > D[c1]+1)){
                sand[c1] = 1;
            }
        }
        if(sand[c1] == 1)sanded.push_back(c1);
    }

    vi D2 = BFS(graph,sand);

    rep(c1,0,n){
        if(D[c1] != D2[c1])return {-1};
    }
    vi res;
    res.push_back(sz(sanded));
    trav(y, sanded){
        res.push_back(y);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n,m;
    cin >> n >> m;
    vi D(n);
    vector<vi> graph(n, vi());

    rep(c1,0,n){
        cin >> D[c1];
    }
    rep(c1,0,m){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vi ans = solve(n,m,D,graph);

    cout << ans[0] << "\n";
    rep(c1,1,sz(ans)){
        cout << ans[c1]+1 << " ";
    }
    if(sz(ans) > 1)cout << "\n";
 
    return 0;
}
