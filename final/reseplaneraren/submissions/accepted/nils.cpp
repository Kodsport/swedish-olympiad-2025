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
const int LOG = 20;

int n,k,q;

vector<vi> C(MAXN, vi());
vector<vi> C2(MAXN, vi());
vector<vi> tram(MAXN, vi());

int DEPTH[MAXN] = {0};
int SS[MAXN] = {0};
int PAR[MAXN] = {0};
int BL[MAXN][LOG] = {0};
int ORDER[MAXN] = {0};
vi inorder;

vi FROM, TO;
vector<vi> subtree(MAXN, vi());
vector<vi> ancestor(MAXN, vi());

void dfs1(int i, int par){
    PAR[i] = par;
    SS[i] = 1;
    ORDER[i] = sz(inorder);
    inorder.push_back(i);
    trav(y, C[i]){
        if(y != par){
            C2[i].push_back(y);
            DEPTH[y] = DEPTH[i]+1;
            dfs1(y,i);
            SS[i] += SS[y];
        }
    }
}

int jump(int i, int steps){
    int ans = i;
    for(int c1 = LOG-1; c1 >= 0; c1--){
        if((1 << c1) <= steps){
            steps -= (1 << c1);
            ans = BL[ans][c1];
        }
    }
    return ans;
}

int dir(int from, int to){
    int d = DEPTH[from]-DEPTH[to]-1;
    return jump(from, d);
}

vi ANS;

void add_trams(int i, map<int,int> &to_map){
    trav(t2, tram[i]){
        int t = ORDER[t2];
        if(to_map.find(t) == to_map.end())to_map[t] = 0;
        to_map[t]++;
    }
}

void rem_trams(int i, map<int,int> &to_map){
    trav(t2, tram[i]){
        int t = ORDER[t2];
        to_map[t]--;
        if(to_map[t] == 0)to_map.erase(t);
    }
}

bool check(int b, map<int,int> &to_map){
    int j = TO[b];
    auto it = to_map.lower_bound(ORDER[j]);
    if(it == to_map.end())return 0;
    int look = (*it).first;
    if(look-ORDER[j] < SS[j]){
        return 1;
    }
    return 0;
}

bool check2(int i, int b, map<int,int> &to_map){
    int j = TO[b];
    if(i != j)j = dir(i,TO[b]);
    auto it = to_map.lower_bound(ORDER[j]+SS[j]);
    if(it != to_map.end())return 1;
    
    auto it2 = to_map.begin();
    if(it2 == to_map.end())return 0;

    if((*it2).first < ORDER[j] + int(i == j))return 1;

    return 0;
}

bool comp(int i, int j){
    return SS[i] > SS[j];
}

map<int,int> dfs3(int i){
    map<int,int> M1;
    if(SS[i] > 1){
        M1 = dfs3(C2[i][0]);
        rep(c1,1,sz(C2[i])){
            map<int,int> M2 = dfs3(C2[i][c1]);
            trav(p, M2){
                int x = p.first;
                int y = p.second;
                if(M1.find(x) == M1.end())M1[x] = 0;
                M1[x] += y;
            }
        }
    }
    add_trams(i, M1);
    trav(b, subtree[i]){
        ANS[b] = check(b, M1);
    }
    trav(b, ancestor[i]){
        ANS[b] = check2(i, b, M1);
    }
    return M1;
}

int lca(int i, int j){
    if(DEPTH[i] > DEPTH[j])swap(i,j);
    j = jump(j, DEPTH[j]-DEPTH[i]);
    for(int c1 = LOG-1; c1 >= 0; c1--){
        if(BL[i][c1] != BL[j][c1]){
            i = BL[i][c1];
            j = BL[j][c1];
        }
    }
    if(i == j)return i;
    return PAR[i];
}

bool LCA[MAXN] = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> k >> q;
    rep(c1,0,n-1){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        C[a].push_back(b);
        C[b].push_back(a);
    }
    rep(c1,0,k){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        tram[a].push_back(b);
        tram[b].push_back(a);
    }

    dfs1(0,0);

    rep(c1,0,n){
        BL[c1][0] = PAR[c1];
    }
    rep(c2,1,LOG){
        rep(c1,0,n){
            BL[c1][c2] = BL[BL[c1][c2-1]][c2-1];
        }
    }

    rep(c1,0,n){
        trav(c2,tram[c1]){
            int c = lca(c1,c2);
            LCA[c] = 1;
        }
    }

    rep(c1,0,q){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        if(ORDER[b] > ORDER[a])swap(a,b);
        FROM.push_back(a);
        TO.push_back(b);
        int c = jump(a, DEPTH[a]-DEPTH[b]);
        if(c == b){
            ancestor[a].push_back(c1);
        }
        else{
            subtree[a].push_back(c1);
        }
        ANS.push_back(-1);
    }
    rep(c1,0,n){
        sort(all(C2[c1]),comp);
    }

    dfs3(0);

    rep(c1,0,q){

        if(FROM[c1] == TO[c1] && LCA[TO[c1]])ANS[c1] = 1;

        if(ANS[c1] == 1){
            cout << "Yes\n";
        }
        if(ANS[c1] == 0){
            cout << "No\n";
        }
        if(ANS[c1] == -1){
            cout << "error\n";
        }
    }
 
    return 0;
}
