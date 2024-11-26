#include "validate.h"
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

bool isAbove(ld k, ld b, ll x, ll y){
    return y > __float128(k) * x + b;
}
ld MAX_VAL = ld(5e9);

int main(int argc, char **argv) {
    init_io(argc, argv);

	int n;
    judge_in >> n;

    vector<pair<ll, ll>> points(2*n);
    for(int i = 0; i < 2*n; i++) {
        judge_in >> points[i].first >> points[i].second;
    }

    auto check = [&](istream& sol, feedback_function feedback){
		ld k, b;
		if (!(sol >> k >> b)) {
			feedback("Expected two floating point numbers or 'impossible'");
		}
		
		if (abs(k) > MAX_VAL) feedback("Too large number");

		int above = 0;
		for (auto [x, y] : points) {
			if (isAbove(k, b, x, y)) above++;
		}
		
		if (above != n) {
			feedback("Line does not split points equally (got %d points above, expected %d)", above, n);
		}
		string trailing;
		if(sol >> trailing) feedback("Trailing output");
	};

	check(judge_ans, judge_error);
	check(author_out, wrong_answer);

    accept();
}
