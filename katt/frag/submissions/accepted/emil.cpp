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
ll t;
ll bestchildren[MAXN];

set<int> goodChildren[MAXN];
int goodParent[MAXN];
int good[MAXN];
vector<int> badChildren[MAXN];



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
        goodParent[c] = node;
        goodChildren[node].insert(c);
        build(c, time + w);

    }
    return;
}



ll dp(int node){
    if (israt[node]){
        bestchildren[node] = e[node];
        return e[node];
    }

    for (auto c: goodChildren[node]){
        bestchildren[node] += dp(c);
    }
    return min(e[node], bestchildren[node]);

}

void merge(int goodnode){
    int p = goodParent[goodnode];
    
    int kept, tossed;
    if (goodChildren[goodnode].size() + badChildren[goodnode].size() > goodChildren[p].size() + badChildren[p].size()){
        kept = goodnode;
        tossed = p;
    }
    else{
        kept = p;
        tossed = goodnode;
    }

    e[kept] = e[p];
    bestchildren[kept] = bestchildren[p];
    goodParent[kept] = goodParent[p];

    goodChildren[goodParent[p]].erase(p);
    goodChildren[goodParent[p]].insert(kept);


    for(int c: badChildren[tossed]){

        good[c] = kept;
        badChildren[kept].push_back(c);

    }

    for (int c: goodChildren[tossed]){
        goodParent[c] = kept;
        goodChildren[kept].insert(c);
    }

    return;




}

void update(int goodnode, ll cost){
     //cout << goodnode << "        " << bestchildren[goodnode] << "-->" << bestchildren[goodnode] - cost << endl;
    bestchildren[goodnode] -= cost;
    ll diff = e[goodnode] - bestchildren[goodnode];
    if (diff > 0){
        merge(goodnode);
        int next = good[goodnode];

        update(next, diff);

    }
    return;
}


int main(){
    
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


    for(int i = 0; i < n; i++){
        badChildren[i].push_back(i);
        good[i] = i;
    }

    build(0, 0);
    sort(rats.begin(), rats.end());
    reverse(rats.begin(), rats.end());

    dp(0);

    for (int i = 0; i < n; i++){
        int goodnode = good[i];
        if (e[goodnode] > bestchildren[goodnode]){
            merge(goodnode);
        }
    }

    ll ans = 0;

    for (int i = 0; i < rats.size(); i++){
        ll time = rats[i].first;
        int node = rats[i].second;

        
        ll dpval = bestchildren[good[0]];
        update(good[node], e[node]);

        if (i == 0){
            ans += (t-time)*dpval;
        }
        else{
            ans += ( rats[i-1].first - time )*dpval;
        }

    }

    cout << ans;






    return 0;
}