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

int n;

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

ll score(vl W){
    sort(all(W));
    reverse(all(W));
    ll res = 0;
    ll s = 1;
    trav(w, W){
        res += s*w;
        s *= -1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;

    vector<pll> SI;
    vector<vl> C;

    int index = 0;
    rep(c1,0,n){
        ll a,b,k;
        cin >> a >> b >> k;
        vl W = choc(a,b);
        int iters = 2 - (k%2);
        rep(iter,0,iters) {
            SI.push_back({score(W), index++});
            C.push_back(W);
        }
    }
    sort(all(SI));
    n = index;

    vl P;
    rep(c1,0,n-1){
        int i = SI[c1].second;
        trav(w, C[i]){
            P.push_back(w);
        }
    }

    ll ans = score(P);
    int i = SI.back().second;
    trav(w, C[i]){
        P.push_back(w);
    }
    ans = min(ans, score(P));

    
    cout << ans << "\n";


    return 0;
}
