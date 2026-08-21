#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define fo(i, n) for(ll i=0;i<((ll)n);i++)
typedef vector<ll> vl;

vl ans;

void solve(ll lo, ll hi){
    ll pos = (lo+hi+1)/2;
    cout << "? " << pos << endl;
    ll res;
    cin >> res;
    if(res == lo || res == hi) return;
    ans.push_back(res);
    solve(lo, res);
    solve(res, hi);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll T, st, en;
    cin >> T;

    cout << "? 0" << endl;
    cin >> st;
    cout << "? 1000000000" << endl;
    cin >> en;
    ans.push_back(st);
    ans.push_back(en);

    solve(st, en);

    cout << "! " << ans.size() << "\n"; //när ska man flusha BORDE VARA TYDLIGT!!
    fo(i, ans.size()) cout << ans[i] << " ";
    cout << endl;


    return 0;
}