using namespace std;
#include <bits/stdc++.h>

typedef long long ll;
#define rep(i,a,b) for(ll i = a; i < b; i++)

int main() {
    int n;
    cin >> n;

    vector<pair<ll,int>> arr;

    rep(i,0,n) {
        ll r, c, k; cin >> r >> c >> k;

        ll a = r, b = c;
        while (a > 1 || b > 1) {
            if ((b/2)*a > (a/2)*b) swap(a, b);
            arr.push_back({(a/2)*b, i});
            a = (a+1)/2;
        }
        arr.push_back({1, i});
    }

    sort(arr.rbegin(), arr.rend());
    vector<vector<int>> occs(n);
    int m = arr.size();

    rep(i,0,m) occs[arr[i].second].push_back(i);

    vector<ll> pref(m+1);
    for (int i = 0; i < m; i += 2) pref[i+1] = arr[i].first;
    for (int i = 1; i < m; i += 2) pref[i+1] = -arr[i].first;

    rep(i,1,m+1) pref[i] += pref[i-1];

    auto sum = [&](int l, int r) {
        return pref[r] - pref[l];
    };

    ll best = sum(0, m);
    rep(i,0,n) {
        ll val = sum(0, occs[i][0]);
        int sign = -1;
        rep(j,0,(ll)occs[i].size()-1) {
            val += sign * sum(occs[i][j]+1, occs[i][j+1]);
            sign *= -1;
        }
        val += sign * sum(occs[i].back()+1, m);
        best = min(best, val);
    }

    cout << best << endl;
}