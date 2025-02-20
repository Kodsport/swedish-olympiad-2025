#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;

const int MAXN = 300001;
const ll nils = 1000000007;

int n,m;
vl A,B,CS,X;
vector<vi> I(MAXN, vi());

vl choc(ll r, ll c){
    vl res;
    while(1){
        if(r*c == 1){
            res.push_back(1);
            break;
        }
        ll a1 = (r/2)*c;
        ll a2 = r*(c/2);
        if(a1 < a2){
            res.push_back(a2);
            c = c-c/2;
        }
        else{
            res.push_back(a1);
            r = r-r/2;
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;

    vector<pll> P;
    rep(c1,0,n){
        ll a,b;
        cin >> a >> b;
        vl W = choc(a,b);
        trav(w, W){
            P.push_back({w, c1});
        }
    }
    sort(all(P));
    m = sz(P);

    CS.push_back(0);
    ll s = 1;
    if(m%2 == 0)s = -1;
    rep(c1,0,m){
        pll p = P[c1];
        int i = p.second;
        I[i].push_back(c1);
        ll w = p.first;
        CS.push_back(CS.back()+w*s);
        X.push_back(w*s);
        s *= -1;
    }

    ll ans = CS.back();

    rep(c1,0,n){
        reverse(all(I[c1]));
        ll s = -1;
        ll temp = CS.back();
        trav(i, I[c1]){
            temp += s*X[i];
            temp += 2*s*CS[i];
            s *= -1;
        }
        ans = min(ans, temp);
    }
    cout << ans << "\n";


    return 0;
}
