#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

const int T = 10000;
const double FULL_SCORE = 30;
const int MAXN = 200;
const int MAXM = 1000000;

int main(int argc, char **argv) {
  init_io(argc, argv);
  bool sample = 0;
  for (int i = 4; i < argc; i++) {
    if (string(argv[i]) == "sample") sample = 1;
  }
  ll x,y;
  judge_in >> x >> y;

  int n,m;
  if(!(author_out >> n)){
    wrong_answer("Could not read first integer");
  }
  if(n == -1 && x >= y){
    wrong_answer("Answer is -1 even though x >= y");
  }

  if(n != -1){
      if(n <= 0 || n > MAXN)wrong_answer("n out of bounds");
      vector<vi> graph(n, vi());
      if(!(author_out >> m)){
          wrong_answer("Could not read m");
      }
      if(m < 0 || m > MAXM)wrong_answer("m out of bounds");

      set<pii> edge_set;

      rep(c1,0,m){
        int u,v;
        if(!(author_out >> u >> v)){
            wrong_answer("Could not read %dth edge", c1);
        }
        if(u < 1 || v < 1 || u > n || v > n){
          wrong_answer("Edge %d out of bounds", c1);
        }
        if(u == v){
          wrong_answer("Self-loop");
        }
        if(edge_set.find({u, v}) != edge_set.end()){
          wrong_answer("Duplicate edge (%d, %d)", u, v);
        }
        edge_set.insert({u,v});
        u--;
        v--;
        graph[u].push_back(v);
      }

      vl cookies(n, 0);
      cookies[0] = x;
      rep(_,0,T){
        vl cookies2(n, 0);
        rep(c1,0,n){
          ll d = sz(graph[c1]);
          if(d == 0){
            cookies2[c1] += cookies[c1];
          }
          else{
            cookies2[c1] += cookies[c1]%d;
            trav(y, graph[c1]){
              cookies2[y] += cookies[c1] / d;
            }
          }
        }
        cookies = cookies2;
      }

      if(cookies[n-1] != y){
        wrong_answer("Did not bake y cookies (%d instead of %d)", cookies[n-1], y);
      }

  }

  string garbage;
  author_out >> garbage;
  if (author_out)
    wrong_answer("trailing output, expected eof");

  double score;
  if(n < FULL_SCORE){
    // Also takes care of n = -1
    score = 1.0;
  }
  else{
    score = min(1.0, 20.0 / (n - FULL_SCORE + 20.0));
  }
  score = max(score, 0.0);
  score *= 1000;

  if (sample) score = 0;

  accept_with_score(score);
}
