#include "validator.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


void run() {

  int N = Int(1, 100); Space();
  int K = Int(1, 3); Endl();

  rep(i,0,N) {
    string word = Line();
    assert(1 <= word.length() && word.length() <= 100);
    for (char &c : word) assert('a' <= c && c <= 'z');
  }

  Eof();
}

