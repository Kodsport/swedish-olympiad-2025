using namespace std;
#include <bits/stdc++.h>

typedef long long ll;
#define rep(i,a,b) for(int i = a; i < b; i++)

int main() {
    int n;
    cin >> n;

    vector<pair<ll,ll>> arr(n);
    rep(i,0,n) cin >> arr[i].first >> arr[i].second;

    ll best = 1e18;
    rep(i,-1,n) {
        priority_queue<pair<ll,pair<ll,ll>>> pq;
        rep(j,0,n) if (j != i) {
            auto [a, b] = arr[j];
            if ((a/2)*b < (b/2)*a) swap(a, b);
            
            pq.push({max(1LL, (a/2)*b), arr[j]});
        }

        ll diff = 0, sign = 1;

        while (!pq.empty()) {
            auto [area, _] = pq.top(); pq.pop();
            diff += sign * area;
            sign *= -1;

            auto [a, b] = _;

            if (a == 1 && b == 1) continue;
            
            if ((a/2)*b < (b/2)*a) swap(a, b);
            a = (a+1)/2;

            if ((a/2)*b < (b/2)*a) swap(a, b);
            pq.push({max(1LL, (a/2)*b), {a, b}});
        }

        best = min(best, diff);
    }

    cout << best << endl;
}