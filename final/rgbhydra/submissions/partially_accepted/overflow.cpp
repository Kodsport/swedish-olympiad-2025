#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    int R,G,B,k;
    cin >> R >> G >> B >> k;

    int best = R;

    if (G == 0 && B == 0 && k > 0) {
        G++;
        B++;
        k--;
        R--;
    }


    cout << max(best, R+k) << "\n";
}