#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXN = 2001;

int n,m,q;

int SAND[MAXN][MAXN] = {0};
int BLOCKED[MAXN][MAXN] = {0};
int D[MAXN][MAXN] = {0};

int DX[4] = {0,1,0,-1};
int DY[4] = {1,0,-1,0};

bool inbounds(int i, int j){
    return i >= 0 && j >= 0 && i < n && j < m;
}

bool sand(int i, int j){
    if(BLOCKED[i][j])return 0;
    if(D[i][j] == -1)return 0;
    rep(c3,0,4){
        int i2 = i+DX[c3];
        int j2 = j+DY[c3];
        if(inbounds(i2, j2) && !BLOCKED[i2][j2]){
            if(D[i2][j2] == -1 || D[i2][j2]-D[i][j] > 1)return 1;
        }
    }
    return 0;
}

int startx, starty;

int D2[MAXN][MAXN] = {0};

bool bfs(){
    rep(c1,0,n){
        rep(c2,0,m){
            D2[c1][c2] = -1;
        }
    }
    queue<pii> Q;
    Q.push({startx, starty});
    D2[startx][starty] = 0;
    while(!Q.empty()){
        pii p = Q.front();
        Q.pop();
        int i = p.first;
        int j = p.second;
        if(SAND[i][j])continue;
        rep(c3,0,4){
            int i2 = i+DX[c3];
            int j2 = j+DY[c3];
            if(inbounds(i2, j2) && !BLOCKED[i2][j2] && D2[i2][j2] == -1){
                D2[i2][j2] = D2[i][j]+1;
                Q.push({i2,j2});
            }
        }
    }

    rep(c1,0,n){
        rep(c2,0,m){
            if(D[c1][c2] != D2[c1][c2])return 0;
        }
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m >> q;

    rep(c1,0,n){
        string s;
        //cin >> s;
        rep(c2,0,m){
            /*
            BLOCKED[c1][c2] = (s[c2] == '#');
            if(s[c2] == 'S'){
                startx = c1;
                starty = c2;
            }*/
            BLOCKED[c1][c2] = 0;
        }
    }

    rep(c1,0,n){
        rep(c2,0,m){
            cin >> D[c1][c2];
            if(D[c1][c2] == 0){
                startx = c1;
                starty = c2;
            }
        }
    }

    rep(c4,0,q){
        char ch;
        int x,y;
        cin >> ch >> x >> y;
        x--;
        y--;
        if(ch == '!'){
            cin >> D[x][y];
        }
        else{
            rep(c1,0,n){
                rep(c2,0,m){
                    SAND[c1][c2] = sand(c1,c2);
                }
            }
            bool yes = bfs();
            if(!yes){
                cout << "fel\n";
            }
            else{
                if(SAND[x][y]){
                    cout << "ja\n";
                }
                else{
                    SAND[x][y] = 1;
                    bool yes2 = bfs();
                    if(yes2){
                        cout << "kanske\n";
                    }
                    else{
                        cout << "nej\n";
                    }
                }
            }

        }
    }

    return 0;
}
