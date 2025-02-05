using namespace std;
#include <bits/stdc++.h>

#define rep(i,a,b) for (int i = a; i < b; i++)
#define pb push_back

typedef long long ll;
typedef vector<ll> vi;

ll rows, cols, q;
vector<vector<ll>> d;

mt19937 rng(6215);
ll rand(ll maxr) {
    return uniform_int_distribution<ll>(0, maxr)(rng);
}


int main() {
    cin >> rows >> cols >> q;
    d.resize(rows);

    rep(r,0,rows) {
        d[r].resize(cols);
        rep(c,0,cols) cin >> d[r][c];
    }

    vector<vector<int>> in(rows, vector<int>(cols, 0));
    vector<vector<int>> up(rows, vector<int>(cols, 0));
    vector<vector<int>> imp(rows, vector<int>(cols, 0));

    auto neis = [](int r, int c) {
        vector<pair<int,int>> ret;
        if (r > 0) ret.pb({r-1, c});
        if (r < rows-1) ret.pb({r+1, c});
        if (c > 0) ret.pb({r, c-1});
        if (c < cols-1) ret.pb({r, c+1});
        return ret;
    };

    auto calc = [&](int r, int c) {
        up[r][c] = 0;
        in[r][c] = 0;
        imp[r][c] = 0;
        if (d[r][c] == -1) return;        

        for (auto [R, C] : neis(r, c)) {
            if (d[R][C] > d[r][c] + 1 || d[R][C] == -1) up[r][c]++;
            if (d[R][C] == d[r][c] - 1 && (!(up[R][C]))) in[r][c]++;
        }
        imp[r][c] = (in[r][c] == 0) && (d[r][c] != 0);
    };


    rep(r,0,rows) rep(c,0,cols) calc(r, c);

    int impossible = 0;
    rep(r,0,rows) rep(c,0,cols) {
        if (d[r][c] <= 0) continue;

        if (in[r][c] == 0) imp[r][c] = 1;
        impossible += imp[r][c];
    }

    rep(Q,0,q) {
        char tp;
        cin >> tp;
        if (tp == '?') {
            int r, c; cin >> r >> c; r--; c--;

            if (impossible) cout << "fel\n";
            else if (d[r][c] == -1) cout << "kanske\n";
            else if (up[r][c]) cout << "ja\n";
            else {
                bool maybe = true;
                for (auto [R, C] : neis(r, c)) {
                    if (d[R][C] == d[r][c] + 1 && in[R][C] == 1) maybe = false;
                }
                if (maybe) cout << "kanske\n";
                else cout << "nej\n";
            }
        }

        else {
            int r, c; cin >> r >> c; r--; c--;
            int D; cin >> D;
            d[r][c] = D;

            set<pair<int,int>> affect;
            for (auto [R, C] : neis(r, c)) {
                affect.insert({R, C});
                for (auto [RR, CC] : neis(R, C)) affect.insert({RR, CC});
            }
            for (auto [R, C] : affect) impossible -= imp[R][C];

            rep(i,0,3) {
                for (auto [R, C] : affect) {
                    calc(R, C);
                }
            }

            for (auto [R, C] : affect) impossible += imp[R][C];
        }
    }

}
