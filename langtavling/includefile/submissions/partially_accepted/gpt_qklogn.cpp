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

    if(a == 0) {
        while(q--) {
            long long query;
            cin >> query;
            cout << originalFile[query-1] << '\n';
        }
        return 0;
    }

    int ind = find(include.begin(), include.end(), 1) - include.begin();
    ll A = (ll)ind * (ll) (k+1);  // Matches Python's A = ind*k

    while(q--) {
        long long query;
        cin >> query;

        if (query < (ll)ind*(ll)(k+1) + 1) {
            cout << originalFile[(query-1)%ind] << "\n";
            continue;
        }

        int currRow = -1;
        bool is_include = true;

        for(int currDepth=k; currDepth>=0; currDepth--) {
            int l=0, r=n;
            while(l < r) {
                int m = (l+r)/2;
                ll total = prefix[m] + prefixInclude[m]*lineAmount[currDepth];
                if(total >= query) r = m;
                else l = m+1;
            }
            currRow = l-1;

            if(include[currRow] == 1) {
                ll total = prefix[currRow] + prefixInclude[currRow]*lineAmount[currDepth];
                if(total >= INF || total != total) {  // Python's INF check
                    query -= ind;  // Use precomputed A
                } else {
                    query -= total;
                }
            } else {
                break;
            }
        }


        cout << originalFile[currRow] << '\n';

    }
}