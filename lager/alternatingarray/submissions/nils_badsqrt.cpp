#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXN = 100001;
const int SQRT = 4000;
const int MAXA = 10;

vi A;
int n,q;
ull DP[MAXN / SQRT + 1][MAXA][MAXA] = {0};
ull START[MAXN / SQRT + 1][MAXA] = {0};

int maxb;

void recalc(int block){
    rep(c1,0,MAXA){
        rep(c2,0,MAXA){
            DP[block][c1][c2] = 0;
        }
        START[block][c1] = 0;
    }
    
    rep(c1,SQRT*block, min(n,SQRT*block+SQRT)){
        int a = A[c1];
        rep(i,0,MAXA){
            ull old = DP[block][i][a];
            DP[block][i][a] = START[block][i];
            START[block][i] += START[block][i]-old;
        }
        DP[block][a][a]++;
        START[block][a]++;
    }
}

ull TOT[MAXA][MAXA] = {0};
ull TEMP[MAXA][MAXA] = {0};
ull STA[MAXA] = {0};

ull solve(){
    rep(c1,0,MAXA){
        rep(c2,0,MAXA){
            TOT[c1][c2] = DP[0][c1][c2];
        }
        STA[c1] = START[0][c1];
    }
    rep(b,1,maxb+1){
        rep(c1,0,MAXA){
            rep(c2,0,MAXA){
                TEMP[c1][c2] = TOT[c1][c2];
            }
        }
        rep(c1,0,MAXA){
            rep(c2,0,MAXA){
                ull c = STA[c1]-TEMP[c1][c2];
                rep(c3,0,MAXA){
                    TOT[c1][c3] += c*DP[b][c2][c3];
                }
                TOT[c1][c2] += DP[b][c1][c2];
            }
        }

        rep(c1,0,MAXA){
            STA[c1] = 0;
            rep(c2,0,MAXA){
                STA[c1] += TOT[c1][c2];
            }
        }
    }

    ull ans = 0;
    rep(c1,0,MAXA){
        rep(c2,0,MAXA){
            ans += TOT[c1][c2];
        }
    }
    return ans+1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> q;

    rep(c1,0,n){
        int a;
        cin >> a;
        A.push_back(a);
    }
    maxb = (n-1)/SQRT;

    rep(c1,0,maxb+1){
        recalc(c1);
    }

    ull ans = solve();
    cout << ans << "\n";

    rep(c1,0,q){
        int a,b;
        cin >> a >> b;
        a--;
        A[a] = b;
        recalc(a/SQRT);
        ans = solve();
        cout << ans << "\n";
    }
    

    return 0;
}
