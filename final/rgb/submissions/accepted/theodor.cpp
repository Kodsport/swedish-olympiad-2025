#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define fo(i, n) for(ll i=0;i<((ll)n);i++)
typedef vector<ll> vl;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll r, g, b, k;
    cin >> r >> g >> b >> k;
    if(g || b) cout << r+k;
    else cout << max(r, r+k-2);

    return 0;
}