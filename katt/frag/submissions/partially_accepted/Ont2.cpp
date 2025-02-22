#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100;
const ll T = 101;

vector<pair<int, ll>> graph[MAXN];
bool israt[MAXN];
ll e[MAXN];
vector<pair<int, ll>> children[MAXN];
int parent[MAXN];
bool visited[MAXN];
vector<pair<ll, int>> rats;
bool added[MAXN];
ll t;

ll memo[MAXN][T];


void build(int node){
    visited[node] = true;
    for(auto i: graph[node]){
        int c = i.first;
        int w = i.second;

        if (visited[c]){
            continue;
        
        }
        parent[c] = node;
        children[node].push_back(make_pair(c, w));
        build(c);

    }
    return;
}

ll dp(int node, ll time){
    if (time <= 0){
        return 0;
    }
    if (israt[node]){
        return time*e[node];  
    }

    if (memo[node][time] != -1){
        return memo[node][time];
    }

    ll best = LLONG_MAX;
    for (int i = 0; i <= time; i++){
        ll cur = i*e[node];
        for (auto j: children[node]){

            int c = j.first;
            ll w = j.second;

            cur += dp(c, time - w - i);


        }
        best = min(best, cur);

        
    }
    memo[node][time] = best;
    return best;

}


int main(){

    for (int i = 0; i < MAXN; i++){
        for(int j = 0; j < T; j++){

            memo[i][j] = -1;
        }
    }
    
    int n, m;
    cin >> n >> m >> t;
    int a , b;
    ll w;
    ll tmp;
    for (int i = 0; i < n-1; i++){

        cin >> a >> b >> w;
        graph[a].push_back(make_pair(b, w));
        graph[b].push_back(make_pair(a, w));
    }

    for (int i = 0; i < n-1; i++){
        
        cin >> tmp;
        e[i+1] = tmp;
    }
    e[0] = 10000000000;
    for(int i = 0; i < m; i++){
        cin >> tmp;
        israt[tmp] = true;
    }

    build(0);
    ll ans = dp(0, t);

    cout << ans;



    return 0;
}
