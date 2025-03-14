#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;
typedef unsigned long long ull;

const ll INF = ll(1000000000) * 1000000000;
const int LIM = 1000;

struct bakverk{
    int n = 0;
    vector<vi> C;

    void add_v(){
        vi v;
        C.push_back(v);
        n++;
    }

    void add_edge(int i, int j){
        C[i].push_back(j);
    }

    void fix(){
        rep(c1,0,n){
            rep(c2,0,sz(C[c1])){
                int y = C[c1][c2];
                if(y == -1)C[c1][c2] = n-1;
            }
        }
    }

    ll bake(ll x){
        fix();
        vl stuff(n,0);
        stuff[0] = x;
        rep(_,0,LIM){
            vl stuff2(n,0);
            rep(c1,0,n){
                ll d = sz(C[c1]);
                if(d == 0){
                    stuff2[c1] += stuff[c1];
                }
                else{
                    stuff2[c1] += stuff[c1]%d;
                    trav(y, C[c1]){
                        stuff2[y] += stuff[c1]/d;
                    }
                }
            }
            stuff = stuff2;
        }
        return stuff[n-1];
    }

    void print(){
        vector<pii> edges;
        rep(c1,0,n){
            trav(y, C[c1]){
                edges.push_back({c1+1,y+1});
            }
        }
        cout << n << " " << sz(edges) << "\n";
        trav(p, edges){
            cout << p.first << " " << p.second << "\n";
        }
    }
};

bakverk greedy(int r, int s, ll x, ll y){
    bakverk res;
    res.add_v();
    vi discard, sink;
    rep(c1,0,r){
        discard.push_back(res.n);
        res.add_v();
    }
    sink.push_back(-1);
    rep(c1,0,s-1){
        sink.push_back(res.n);
        res.add_v();
        res.add_edge(res.n-1, -1);
    }

    int now = 0;
    while(1){
        if(y == 0)break;
        if(x == y){
            res.add_edge(now, -1);
            break;
        }
        for(ll d = 2; d >= 2; d--){
            if(x-x%d < y)continue;
            ll a = x/d;
            ll y2 = y%a;
            ll s2 = y/a;
            ll r2 = d-s2-1;

            bool no_now = 0;

            if(y2 == 0){
                if(s2 <= s && r2 < r){
                    no_now = 1;
                    r2++;
                }
                else{
                    if(d == 2 && s2 == s+1){
                        res.add_edge(now, -1);
                        res.add_v();
                        res.add_edge(now, res.n-1);
                        res.add_edge(res.n-1,-1);
                        x = 0;
                        y = 0;
                        break;
                    }
                }
            }

            if(r2 <= r && s2 <= s){
                rep(c1,0,r2){
                    res.add_edge(now, discard[c1]);
                }
                rep(c1,0,s2){
                    res.add_edge(now, sink[c1]);
                }

                y = y2;
                x = a;  
                if(no_now)break;
                res.add_v();
                res.add_edge(now,res.n-1);
                now = res.n-1; 
                break;
            }
            
        }
    }
    res.add_v();
    return res;
}

ll rnd(){
    ull R = 0;
    rep(c1,0,7){
        R *= ull(RAND_MAX);
        R += rand();
    }
    return R%INF;
}

int main() {

    ll x,y;
    cin >> x >> y;
    if(y > x){
        cout << "-1\n";
        return 0;
    }
    ll mi = INF;
    bakverk ans = greedy(1,1,x,y);
    ans.fix();

    ans.print();

    return 0;
}