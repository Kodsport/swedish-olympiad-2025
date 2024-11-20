// Python -> C++ using chatgpt + some hand optimization
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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


struct Tree {
    typedef p2 T;
    static constexpr T unit = p2(-1, -1);
    T f(T a, T b) { return max(a, b); } // (any associative fn)
    vector<T> s; int n;
    Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) { // query [b, e)
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

int prefmax[1000][1000];
ll prefsum[1000][1000];
ll prefmaxcum[1000][1000];
int sufmax[1000][1000];
ll sufsum[1000][1000];
ll sufmaxcum[1000][1000];
vi h;

// Make block_size a compile-time constant
template<int block_size>
void update_block(int block_ind) {
    int base = block_ind * block_size;
    int p = 0;

    for (int i = 0; i < block_size; i++) {
        p = max(p, h[base + i]);
        prefmax[block_ind][i] = p;
        prefsum[block_ind][i] = h[base + i];
        prefmaxcum[block_ind][i] = p - h[base + i];
        if (i != 0) {
            prefsum[block_ind][i] += prefsum[block_ind][i - 1];
            prefmaxcum[block_ind][i] += prefmaxcum[block_ind][i - 1];
        }
    }

    // Not very DRY, but runs faster this way
    p = 0;
    for (int i = block_size - 1; i >= 0; i--) {
        p = max(p, h[base + i]);
        sufmax[block_ind][i] = p;
        sufsum[block_ind][i] = h[base + i];
        sufmaxcum[block_ind][i] = p - h[base + i];
        if (i != block_size - 1) {
            sufsum[block_ind][i] += sufsum[block_ind][i + 1];
            sufmaxcum[block_ind][i] += sufmaxcum[block_ind][i + 1];
        }
    }
}

int n;
template<int block_size>
ll query(int l, int r, int idx)
{
    ll ans = 0;

    // Left to middle
    int l_block = l / block_size;
    ll level = 0;
    for (int i = l; i < min(idx, (l_block + 1) * block_size); ++i) {
        level = max(level, (ll)h[i]);
        ans += level - h[i];
    }

    int mid_block = idx / block_size;
    for (int block_ind = l_block + 1; block_ind < mid_block; ++block_ind) {
        if (level >= prefmax[block_ind][block_size - 1]) {
            ans += level * block_size - prefsum[block_ind][block_size - 1];
        }
        else {
            int lo = -1, hi = block_size;
            while (lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if (prefmax[block_ind][mid] >= level) {
                    hi = mid;
                }
                else {
                    lo = mid;
                }
            }
            ans += level * (lo + 1) + prefmaxcum[block_ind][block_size - 1];
            if (lo >= 0) {
                ans -= prefsum[block_ind][lo];
                ans -= prefmaxcum[block_ind][lo];
            }

            level = prefmax[block_ind][block_size - 1];
        }
    }

    if (l_block != mid_block) {
        for (int i = mid_block * block_size; i < idx; ++i) {
            level = max(level, (ll)h[i]);
            ans += level - h[i];
        }
    }

    // Right to middle
    // Not very DRY, but runs faster this way
    int r_block = r / block_size;
    level = 0;
    for (int i = r; i >= max(idx, r_block * block_size); --i) {
        level = max(level, (ll)h[i]);
        ans += level - h[i];
    }

    for (int block_ind = r_block - 1; block_ind > mid_block; --block_ind) {
        if (level >= sufmax[block_ind][0]) {
            ans += level * block_size - sufsum[block_ind][0];
        }
        else {
            int lo = -1, hi = block_size;
            while (lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if (sufmax[block_ind][mid] >= level) {
                    lo = mid;
                }
                else {
                    hi = mid;
                }
            }
            ans += level * (block_size - hi) + sufmaxcum[block_ind][0];
            if (hi < block_size) {
                ans -= sufsum[block_ind][hi];
                ans -= sufmaxcum[block_ind][hi];
            }
            level = sufmax[block_ind][0];
        }
    }

    if (r_block != mid_block) {
        for (int i = min(n - 1, (mid_block + 1) * block_size - 1); i > idx; --i) {
            level = max(level, (ll)h[i]);
            ans += level - h[i];
        }
    }
    return ans;
}

const int SIZE_1 = 200;
const int SIZE_2 = 270;
const int SIZE_3 = 900;

signed main()
{
    fast();

    int q;
    cin >> n >> q;

    h.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    vector<tuple<int, int, int>> queries;
    int num_updates = 0;

    for (int i = 0; i < q; ++i) {
        int t, a, b;
        cin >> t >> a >> b;
        queries.emplace_back(t, a, b);
        if (t == 2) {
            num_updates++;
        }
    }

    double update_percent = double(num_updates) / q;
    int block_size;
    if (update_percent > 0.65) block_size = SIZE_1;
    else if (update_percent > 0.45) block_size = SIZE_2;
    else block_size = SIZE_3;

    while (n % block_size != 0) {
        h.push_back(0);
        n++;
    }

    Tree tree(n);
    rep(i, n) tree.update(i, p2(h[i], i));

    auto update_wrapper = [&](int ind)
    {
        if (block_size == SIZE_1) update_block<SIZE_1>(ind);
        if (block_size == SIZE_2) update_block<SIZE_2>(ind);
        if (block_size == SIZE_3) update_block<SIZE_3>(ind);
    };

    rep(i, n/block_size) {
        update_wrapper(i);
    }

    auto query_wrapper = [&](int l, int r, int idx)
    {
        if (block_size == SIZE_1) return query<SIZE_1>(l, r, idx);
        if (block_size == SIZE_2) return query<SIZE_2>(l, r, idx);
        if (block_size == SIZE_3) return query<SIZE_3>(l, r, idx);
    };

    for (const auto& [t, a, b] : queries)
    {
        if (t == 1)
        {
            int l = a - 1, r = b - 1;
            int idx = tree.query(l, r + 1).second;
            
            cout << query_wrapper(l,r,idx) << "\n";
        }
        else
        {
            int ind = a - 1;
            h[ind] += b;
            tree.update(ind, { h[ind], ind });
            update_wrapper(ind/block_size);
        }
    }

    return 0;
}
