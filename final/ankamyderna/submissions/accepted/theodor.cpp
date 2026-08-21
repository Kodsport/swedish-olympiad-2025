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

    ll lo = 0, hi = m+1;
    while(hi-lo > 1){
        ll mid = (lo+hi)/2;

        vl temp = a;
        bool fail = false;
        fo(i, mid){
            temp[c[i]]-=(mid-i)*(mid-i);
            if(temp[c[i]] < 0){
                fail = true;
                break;
            }
        }

        if(!fail) lo = mid;
        else hi = mid;
    }
    cout << lo << endl;

    return 0;
}