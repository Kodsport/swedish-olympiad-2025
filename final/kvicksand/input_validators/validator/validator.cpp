#include "validator.h"

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

bool connected(vector<vi> &graph){
    vi no_sand(sz(graph), 0);
    vi D = BFS(graph, no_sand);
    trav(y, D){
        if(y == -1)return 0;
    }
    return 1;
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

void run() {
    bool line = Arg("line", 0);
    bool tree = Arg("tree", 0);
    bool possible = Arg("possible", 0);

    int n = Int(2, 300000);
    Space();
    int m = Int(n-1, 300000);
    Endl();
    vi D = SpacedInts<int>(n, -1, n);

    vector<vi> graph(n, vi());
    set<pii> S;

    for(int c1 = 0; c1 < m; c1++){
        int a = Int(1, n);
        Space();
        int b = Int(1, n);
        Endl();
        assert(a != b);
        assert(S.find({a, b}) == S.end());
        S.insert({a, b});
        S.insert({b, a});
        if(line){
            assert(a == c1+1 && b == c1+2);
        }
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    assert(D[0] == 0);
    assert(connected(graph));
    if(tree || line)assert(m == n-1);
    
    if(possible){
        assert(solve(n,m,D,graph)[0] != -1);
    }

    Eof();
}

