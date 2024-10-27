#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

mt19937 rng((random_device())());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]

#include "communication.h"

const int mod = int(1e9 + 7);
int hashf(string x)
{
    ll ret = 0;
    repe(v, x)
    {
        ret = (ret + (v == '1' ? 1 : 0)) * 31 % mod;
    }
    return ret;
}

const int k = 50;
string hashstring(string x, int d=4)
{
    string ret(k,'0');

    int h = hashf(x);
    rep(j, k)
    {
        if (h & (1 << j)) ret[j] = '1';
    }

    if (d) return hashstring(ret, d - 1);
    else return ret;
}

string encode(int _, int __, string x)
{
    return x + hashstring(x);
}

string decode(int _, int __, string x)
{
    rep(i, sz(x))
    {
        repp(j, i, sz(x))
        {
            string u(x);

            repp(k, i, j + 1)
            {
                if (u[k] == '1') u[k] = '0';
                else u[k] = '1';
            }

            // meat is guess for message content
            string meat = u.substr(0, sz(x) - k);
            string encoded = encode(_, __, meat);
            if (u == encoded)
            {
                return meat;
            }
        }
    }
    assert(0);
    return "its joever";
}
