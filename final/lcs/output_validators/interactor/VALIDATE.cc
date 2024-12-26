#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

const int MAX_QUERIES = 25000;

const int sigma = 26;
typedef unsigned long long ull;
int LCS(const string& s1, const string& s2)
{
    const string& a = sz(s1) > sz(s2) ? s2 : s1;
    const string& b = sz(s1) > sz(s2) ? s1 : s2;

    int numblocks = (sz(a) + 2 + 63) / 64;
    vector<ull> dp(numblocks, numeric_limits<ull>::max());

    auto unset = [&](int ind, vector<ull>& arr)
        {
            arr[ind / 64] |= (1ULL << (ind%64));
        };

    vector<ull> occs[26];
    rep(s, 0, 26) occs[s] = vector<ull>(numblocks);
    
    rep(i, 0, sz(a))
    {
        unset(i, occs[a[i] - 'a']);
    }

    for (char c : b)
    {
        vector<ull>& occ = occs[c-'a'];

        ull carry = 0;

        rep(i, 0, numblocks)
        {
            ull s;
            carry = __builtin_uaddll_overflow(carry, dp[i], &s) | __builtin_uaddll_overflow(s, (dp[i] & occ[i]), &s);
            dp[i] = (s | (dp[i] & ~occ[i]));
        }
    }
    int ret = 0;
    rep(i, 0, numblocks) ret += __builtin_popcountll(dp[i]);
    return 64 * numblocks - ret;
}

int LCSslow(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();

    // Create a DP table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp.back().back();
}

int main(int argc, char **argv) {
    init_io(argc, argv);

    int N, K;
    judge_in >> N >> K;
    string hidden;
    judge_in >> hidden;
    
    cout << N << " " << K << endl;

	char qtype;
	int qcount = 0;
	for (;;) {
		cin >> qtype;
		if (!cin) wrong_answer("EOF");
		if (qtype == '?') {
			string guess;
            cin >> guess;
			if (!cin) wrong_answer("EOF2");
            // TODO: validate guess

			++qcount;
			if (qcount > MAX_QUERIES) {
				wrong_answer("too many queries");
			}
            //assert(LCS(hidden, guess) == LCSslow(hidden, guess));
			cout << LCS(hidden, guess) << endl;

		} else if (qtype == '!') {
			break;
		} else {
			wrong_answer("Invalid query type %c", qtype);
		}
	}

    string ans;
    cin >> ans;

    if (ans != hidden) wrong_answer("found wrong hidden string");

	string trailing;
	if (cin >> trailing){
		wrong_answer("Trailing output");
	}

	// TODO: score depending on qcount
	accept_with_score(qcount);

}
