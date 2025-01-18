#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    ll R,G,B,k;
    cin >> R >> G >> B >> k;

    ll best = R;
    while (k--) {
        if (G != 0) {
            R++;
            G--;
            B++;
        }
        else if (B != 0){
            R++;
            G++;
            B--;
        }
        else {
            R--;
            G++;
            B++;
        }
    }

    cout << max(best,R) << "\n";
}