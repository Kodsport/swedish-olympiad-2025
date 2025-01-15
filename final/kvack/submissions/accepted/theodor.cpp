#include <bits/stdc++.h>
using namespace std;


#define ll long long
#define INF ((ll)(1e9+7))
#define fo(i, n) for(ll i=0;i<((ll)n);i++)
#define deb(x) cout << #x << " = " << (x) << endl;
#define deb2(x, y) cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define LSOne(S) ((S) & (-S))
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<vpii> vvpii;
typedef vector<vpl> vvpl;

vl ans;

void solve(ll lo, ll hi){
    ll pos = (lo+hi+1)/2;
    cout << "? " << pos << endl;
    ll res;
    cin >> res;
    if(res == lo || res == hi) return;
    ans.pb(res);
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
    ans.pb(st);
    ans.pb(en);

    solve(st, en);

    cout << "! " << ans.size() << "\n"; //när ska man flusha BORDE VARA TYDLIGT!!
    fo(i, ans.size()) cout << ans[i] << " ";
    cout << endl;


    return 0;
}