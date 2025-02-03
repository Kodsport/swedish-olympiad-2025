#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXN = 300001;

int n,m,q;

vector<vi> C1(MAXN, vi());
vector<vi> C2(MAXN, vi());

vi blocked;
vi sand;
vi bad;
vi D;

int bads = 0;
int start;

int DX[4] = {0,1,0,-1};
int DY[4] = {1,0,-1,0};

bool inbounds(int i, int j){
    return i >= 0 && j >= 0 && i < n && j < m;
}

pii tp(int i){
    return {i/m, i%m};
}

int ti(int x, int y){
    return x*m+y;
}

bool adj(int i, int j){
    pii p1 = tp(i);
    pii p2 = tp(j);
    return abs(p1.first-p2.first) + abs(p1.second-p2.second) == 1;
}

bool parent(int i, int j){
    if(blocked[i] || blocked[j])return 0;
    if(sand[i])return 0;
    if(D[i] == -1 || D[j] == -1)return 0;
    return D[i] == D[j]-1;
}

bool is_sand(int i){
    if(blocked[i] || D[i] == -1)return 0;
    bool res = 0;
    trav(y, C1[i]){
        if(D[y] == -1 || D[y]-D[i] > 1)res = 1;
    }
    return res;
}

int num_parents(int i){
    int res = 0;
    trav(y, C1[i]){
        if(parent(y,i))res++;
    }
    return res;
}

bool is_bad(int i){
    if(blocked[i])return 0;
    if(i == start){
        return (D[i] != 0);
    }
    if(D[i] == -1)return 0;
    return (num_parents(i) == 0);
}

void update_bad(int i){
    bads -= bad[i];
    bad[i] = is_bad(i);
    bads += bad[i];
}

string answer(int i){
    if(bads > 0 || D[start] != 0)return "fel";
    if(sand[i])return "ja";
    trav(y, C1[i]){
        if(parent(i, y) && num_parents(y) == 1)return "nej";
    }
    return "kanske";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m >> q;

    rep(c1,0,n){
       // string s;
       // cin >> s;
        rep(c2,0,m){
            sand.push_back(0);
            bad.push_back(0);
            D.push_back(-1);
            //blocked.push_back((s[c2] == '#'));
            blocked.push_back(0);
            //if(s[c2] == 'S')start = ti(c1,c2);
        }
    }

    rep(c1,0,n){
        rep(c2,0,m){
            int i = ti(c1,c2);
            if(blocked[i])continue;
            rep(c3,0,4){
                int x = c1+DX[c3];
                int y = c2+DY[c3];
                if(inbounds(x, y) && !blocked[ti(x,y)]){
                    int j = ti(x,y);
                    C1[i].push_back(j);
                }
            }
        }
    }

    rep(i,0,n*m){
        if(blocked[i])continue;
        set<int> S;
        trav(y, C1[i]){
            S.insert(y);
            trav(yy, C1[y]){
                S.insert(yy);
            }
        }
        trav(y, S){
            C2[i].push_back(y);
        }
    }

    rep(c1,0,n){
        rep(c2,0,m){
            cin >> D[ti(c1,c2)];
            if(D[ti(c1,c2)] == 0){
                start = ti(c1,c2);
            }
        }
    }

    rep(c1,0,n*m){
        sand[c1] = is_sand(c1);
    }

    rep(c1,0,n*m){
        update_bad(c1);
    }

    rep(c1,0,q){
        char ch;
        int x,y;
        cin >> ch >> x >> y;
        x--;
        y--;
        int i = ti(x,y);
        if(ch == '?'){
            cout << answer(i) << "\n";
        }
        else{
            int to;
            cin >> to;
            D[i] = to;
            sand[i] = is_sand(i);
            trav(y, C1[i]){
                sand[y] = is_sand(y);
            }
            trav(y, C2[i]){
                update_bad(y);
            }
        }
    }

    return 0;
}
