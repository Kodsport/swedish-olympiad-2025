#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    int n, k;
    cin >> n >> k;

    auto query = [](string x)
        {
            cout << "? " << x << endl;
            int resp;
            cin >> resp;
            return resp;
        };

    vector<pair<int, char>> occs;
    rep(i, k)
    {
        occs.emplace_back(query(string(n, i + 'a')), i + 'a');
    }
    sort(all(occs));
    reverse(all(occs));

    string s = string(occs[0].first, occs[0].second);

    char c = occs[1].second;
    rep(i, sz(s) + 1)
    {
        if (sz(s) == n) break;
        string cop(s);
        cop.insert(cop.begin() + i, c);
        if (query(cop) == sz(cop))
        {
            s = cop;
        }
    }

    cout << "! " << s;

    return 0;
}
