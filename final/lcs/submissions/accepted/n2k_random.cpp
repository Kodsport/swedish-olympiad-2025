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

    vector<char> alpha;
    repp(c, 'a', 'a' + k)
    {
        alpha.push_back(c);
    }
    mt19937 rng(10);
    string s;
    while (sz(s) < n)
    {
        rep(i, sz(s) + 1)
        {
            shuffle(all(alpha), rng);
            repe(c, alpha)
            {
                string cop(s);
                cop.insert(cop.begin() + i, c);
                if (query(cop) == sz(cop))
                {
                    s = cop;
                    goto done;
                }
            }
        }

    done:;
    }
    cout << "! " << s;

    return 0;
}
