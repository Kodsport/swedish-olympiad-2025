// Chatgpt translated from harry.py
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define ll __int128_t

const ll INF = 1e12;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, q;
    cin >> n >> k >> q;
    cin.ignore();

    vector<string> originalFile(n);
    for (int i = 0; i < n; ++i) {
        getline(cin, originalFile[i]);
    }

    vector<int> include(n, 0);
    int a = 0, x = 0;
    for (int i = 0; i < n; ++i) {
        if (originalFile[i] == "#include \"main.hpp\"") {
            include[i] = 1;
            a++;
        } else {
            x++;
        }
    }

    vector<ll> apowers;
    apowers.push_back(1);
    for (int i = 0; i < k + 1; ++i) {
        ll next_val = apowers.back() * a;
        if (next_val > INF) {
            next_val = INF;
        }
        apowers.push_back(next_val);
    }

    vector<ll> prefixApowers;
    prefixApowers.push_back(0);
    for (auto num : apowers) {
        prefixApowers.push_back(prefixApowers.back() + num);
        if (prefixApowers.back() > INF) prefixApowers[sz(prefixApowers)-1] = INF;
    }

    vector<ll> lineAmount;
    lineAmount.push_back(1);
    for (int rec = 1; rec <= k + 1; ++rec) {
        ll val = prefixApowers[rec] * x + apowers[rec];
        if (val > INF) val = INF;
        lineAmount.push_back(val);
    }

    vector<ll> prefix(n + 1, 0);
    vector<ll> prefixInclude(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + (1 - include[i]);
        prefixInclude[i + 1] = prefixInclude[i] + include[i];
    }

    if (a == 0) {
        for (int i = 0; i < q; ++i) {
            long long query;
            cin >> query;
            cout << originalFile[query - 1] << '\n';
        }
        return 0;
    }

    int ind = -1;
    for (int i = 0; i < n; ++i) {
        if (include[i] == 1) {
            ind = i;
            break;
        }
    }

    for (int i = 0; i < q; ++i) {
        long long query;
        cin >> query;

        if (query < (ll)ind * (k + 1) + 1) {
            int ans_idx = (query - 1) % ind;
            cout << originalFile[ans_idx] << '\n';
            continue;
        }

        ll ans = -1;
        int currMaxk = k;

        while (currMaxk > 0) {
            if (query < (ll)ind * (currMaxk + 1) + 1) {
                ans = (query - 1) % ind;
                break;
            }

            int hi = currMaxk;
            int lo = 0;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                ll subtracted = (currMaxk - mid) * (ll)ind;
                if (query - subtracted > lineAmount[mid + 1]) {
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
            }

            query -= (currMaxk - lo) * (ll)ind;
            if (lo == 0) {
                break;
            }

            int l = 0, r = n;
            while (l < r) {
                int m = (l + r) / 2;
                ll total = prefix[m] + prefixInclude[m] * lineAmount[lo];
                if (total == query) {
                    l = m;
                    r = m;
                } else if (total > query) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }

            int currRow = l - 1;

            if (include[currRow] == 0) {
                ans = currRow;
                break;
            } else {
                query -= prefix[currRow] + prefixInclude[currRow] * lineAmount[lo];
                currMaxk = lo - 1;
            }
        }

        if (ans != -1) {
            cout << originalFile[ans] << '\n';
        } else {
            cout << originalFile[query - 1] << '\n';
        }
    }

    return 0;
}