#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    vi heights(n);
    rep(i, n) cin >> heights[i];

    while (q--)
    {
        int t;
        cin >> t;
        if (t==1)
        {
            int i, v;
            cin >> i >> v;
            i--;
            heights[i] = v;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            l--; r--;

            int ans = 0;
            repp(i, l, r + 1)
            {
                int r_hi = -1;
                int l_hi = -1;

                repp(j, i + 1, r + 1)
                {
                    r_hi = max(r_hi, heights[j]);
                }
                repp(j, l, i)
                {
                    l_hi = max(l_hi, heights[j]);
                }

                int lim = min(l_hi, r_hi);
                if (lim>heights[i])
                {
                    ans += lim - heights[i];
                }
            }
            cout << ans << "\n";
        }
    }

    return 0;
}
