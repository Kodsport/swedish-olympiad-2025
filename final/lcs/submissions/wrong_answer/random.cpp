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

    mt19937 rng;
    uniform_int_distribution<int> dist(0, k - 1);

    while (true)
    {
        string s;
        rep(i, n) s += (char)(dist(rng) + 'a');
        cout << "? " << s << endl;
        int resp;
        cin >> resp;
        if (resp==n)
        {
            cout << "! " << s << endl;
            return 0;
        }
    }

    return 0;
}
