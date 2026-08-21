#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define fo(i, n) for(ll i=0;i<((ll)n);i++)
typedef vector<ll> vl;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, m;
    cin >> n >> m;

    vl a(n), c(m);
    fo(i, n) cin >> a[i];

    fo(i, m){
        cin >> c[i];
        c[i]--;
    }

    ll ans = -1;
    fo(mid, m+1){

        vl temp = a;
        bool fail = false;
        fo(i, mid){
            temp[c[i]]-=(mid-i)*(mid-i);
            if(temp[c[i]] < 0){
                fail = true;
                break;
            }
        }
        if(fail)break;
        ans++;
    }
    cout << ans << endl;

    return 0;
}