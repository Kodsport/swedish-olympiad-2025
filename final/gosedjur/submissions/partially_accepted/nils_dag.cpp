#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXN = 400001;

int n,r,c;

vector<vi> C(MAXN, vi());
int indeg[MAXN] = {0};
set<pii> edge_set;

int L[MAXN] = {0};
int R[MAXN] = {0};

vector<vi> grid;

bool inbounds(int i, int j){
    return i >= 0 && j >= 0 && i < r && j < c;
}

void add_edge(int i, int j){
    if(i == j || edge_set.find({i, j}) != edge_set.end())return;
    edge_set.insert({i,j});
    indeg[j]++;
    C[i].push_back(j);
}

int order[MAXN] = {0};
vi TS;
int ANS[MAXN] = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> r >> c;
    if(n > 30000)return 0;
    rep(c1,0,n){
        L[c1] = 10000000;
        R[c1] = -L[c1];
    }

    rep(c1,0,r){
        vi row;
        rep(c2,0,c){
            int a;
            cin >> a;
            a--;
            L[a] = min(L[a], c2);
            R[a] = max(R[a], c2);
            row.push_back(a);
        }
        grid.push_back(row);
    }

    rep(c1,0,r-1){
        rep(c2,0,c){
            add_edge(grid[c1][c2], grid[c1+1][c2]);
        }
    }

    rep(c1,0,n){
        order[c1] = -1;
    }

    vi Q;
    rep(c1,0,n){
        if(indeg[c1] == 0){
            Q.push_back(c1);
        }
    }
    while(!Q.empty()){
        int a = Q.back();
        Q.pop_back();
        order[a] = sz(TS);
        TS.push_back(a);
        trav(b, C[a]){
            indeg[b]--;
            if(indeg[b] == 0) Q.push_back(b);
        }
    }

    rep(c1,0,n){
        if(order[c1] == -1)ANS[c1] = -1;
    }
    rep(c1,0,sz(TS)){
        int i = TS[c1];
        ANS[i] = 0;
        int lo = L[i];
        int hi = R[i];
        for(int c2 = c1-1; c2 >= 0; c2--){
            int j = TS[c2];
            if(!(R[j] < lo || L[j] > hi)){
                ANS[i]++;
                lo = min(lo, L[j]);
                hi = max(hi, R[j]);
            }
        }
    }

    rep(c1,0,n){
        cout << ANS[c1] << " ";
    }cout << "\n";

    return 0;
}
