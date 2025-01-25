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

const int MAX_QUERIES = 10000;

int dp[101][101];

int LCS(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++)
            dp[i][j]=0;
    }

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

    return dp[m][n];
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
            for (auto c : guess) {
                if (!(c >= 'a' && c <= 'a'+K-1)) {
                    author_message("Guess contains invalid character");
                    wrong_answer("Invalid character in guess");
                }
            }
            if (sz(guess) > N) {
                author_message("Guess is too long");
                wrong_answer("Too long guess");
            }

			qcount++;
			if (qcount > MAX_QUERIES) {
                author_message("Too many guesses");
				wrong_answer("too many queries");
			}
			cout << LCS(hidden, guess) << endl;
		} else if (qtype == '!') {
			break;
		} else {
            author_message("Made invalid type of query (not ? or !)");
			wrong_answer("Invalid query type %c", qtype);
		}
	}

    string ans;
    cin >> ans;

    if (ans != hidden)
    {
        author_message("Found wrong password");
        wrong_answer("found wrong hidden string");
    }


	string trailing;
	if (cin >> trailing){
		wrong_answer("Trailing output");
	}

	// feeling lucky?
    if (qcount == 0) accept_with_score(1);
	else accept_with_score(min(1.0, 666.0/qcount));

}
