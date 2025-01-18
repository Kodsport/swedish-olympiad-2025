#include <bits/stdc++.h>

#define all(x)  (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()

using namespace std;

typedef long long ll;

ll linf = 1e15+1;

inline void scoobydoobydoo(){
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

const int MAXN = 3e5+7;
int nDist[MAXN];
vector<int> adj[MAXN];
bool isVisited[MAXN];
bool isSandi[MAXN];

int main(){
    scoobydoobydoo();
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++)cin >> nDist[i];

    for (int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> sands;

    queue<pair<int, int>> q; //node, w

    q.push({0, 0});
    isVisited[0] = true;

    while(!q.empty()){
        int node = q.front().first;
        int w = q.front().second;
        q.pop();
        vector<int> addi;
        bool isSand = false;
        bool impossible = false;
        for (auto e : adj[node]){
            if (!isVisited[e]){
                if (nDist[e] == w+1) addi.push_back(e);
                else isSand = true;
            }
        }
        if (!isSand){
            for (auto e : addi){
                q.push({e, w+1});
                isVisited[e] = true;
            }
        }
        else {
            sands.push_back(node+1);
            isSandi[node] = true;
        }
        
    }

    q.push({0, 0});

    for (int i = 0; i < n; i++)isVisited[i] = false;

    isVisited[0] = true;


    while (!q.empty()){
        int node = q.front().first;
        int w = q.front().second;
        q.pop();
        if (nDist[node] != w){
            cout << -1 << endl;
            return 0;
        }
        if (isSandi[node])continue;
        for (auto e : adj[node]){
            if (!isVisited[e]){
                q.push({e, w+1});
                isVisited[e] = true;
            }
        }
    }

    for (int i = 0; i < n; i++){
        if (!isVisited[i] && nDist[i] != -1){
            cout << -1 << endl;
            return 0;
        }
    }

    cout << sands.size() << endl;
    for (auto e : sands)cout << e << " ";
    cout << endl;
    

    return 0;
}