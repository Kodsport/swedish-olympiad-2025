#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1000;
const ll T = 1001;

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

    

    int lo = 0;
    int hi = time;

    while (hi > lo){
        int mid1 = lo + (hi-lo)/3;
        int mid2 = mid1 + (hi-lo)/3 + 1;

        ll cur1 = mid1*e[node];
        for (auto j: children[node]){

            int c = j.first;
            ll w = j.second;

            cur1 += dp(c, time - w - mid1);


        }

        ll cur2 = mid2*e[node];
        for (auto j: children[node]){

            int c = j.first;
            ll w = j.second;

            cur2 += dp(c, time - w - mid2);


        }

        if (cur1 <= cur2){
            hi = mid2 -1;

        }
        else {
            lo = mid1 + 1;
        }


    }

    ll best = lo*e[node];
    for (auto j: children[node]){

        int c = j.first;
        ll w = j.second;

        best += dp(c, time - w - lo);
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
