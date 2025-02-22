#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 2e5;

vector<pair<int, ll>> graph[MAXN];
bool israt[MAXN];
ll e[MAXN];
vector<int> children[MAXN];
int parent[MAXN];
bool visited[MAXN];
vector<pair<ll, int>> rats;
bool added[MAXN];
ll bestchildren[MAXN];
ll t;


void build(int node, ll time){
    visited[node] = true;
    if (israt[node]){
        rats.push_back( make_pair(time, node));
        return;
    }
    for(auto i: graph[node]){
        int c = i.first;
        int w = i.second;

        if (visited[c]){
            continue;
        }
        if (time + w >= t){
            continue;
        }
        parent[c] = node;
        build(c, time + w);

    }
    return;
}

void add(int node, ll cost){
    //if (cost == 0){  //cheese
    //    return;
    //}
    ll old = min(e[node], bestchildren[node]);
    bestchildren[node] += cost;
    ll neww = min(e[node], bestchildren[node]);
    
    if (node != 0){
        int p = parent[node];
        add(p, neww - old);
    }
    return;
}

ll dp(int node){
    if (israt[node]){
        return e[node];
    }

    ll sumchildren = 0;
    for (auto c: children[node]){
        sumchildren += dp(c);
    }
    return min(e[node], sumchildren);

}


int main(){
    added[0] = true;
    e[0] = LLONG_MAX;
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
    for(int i = 0; i < m; i++){
        cin >> tmp;
        israt[tmp] = true;
    }

    build(0, 0);
    sort(rats.begin(), rats.end());

    ll ans = 0;

    for (int i = 0; i < rats.size(); i++){
        ll time = rats[i].first;
        int node = rats[i].second;

        add(node, e[node]);
        ll dpval = bestchildren[0];

        if (i == rats.size()-1){
            ans += (t-time)*dpval;
        }
        else{
            ans += (rats[i+1].first - time)*dpval;
        }

    }

    cout << ans;






    return 0;
}
