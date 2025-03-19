#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, b) for(int i = 0; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vi;

int main(int argc, char **argv) {
  init_io(argc, argv);

  int n;
  judge_in >> n;

  vi brines(n);
  for (ll& b : brines) judge_in >> b;

  auto check = [&](istream& sol, feedback_function feedback){
    ll score;
    if(!(sol >> score)) feedback("Expected more output");
    vi perm(n);
    vi seen(n);
    for (ll& v : perm)
    {
      if (!(sol >> v)) return make_pair(score, false);
      if (v < 0 || v >= n) return make_pair(score, false);
      if (seen[v]) return make_pair(score, false);
      seen[v] = 1;
    }
    vi permuted(n);
    rep(i,n) permuted[i] = brines[perm[i]];
    ll score_from_construction = 0;
    vi seen2(n);
    vi order;
    rep(i,n-1)
    {
      int x;
      if (!(sol >> x)) return make_pair(score, false);
      if (x < 0 || x >= n) return make_pair(score, false);
      order.push_back(x);
    }

    vi nxt(n);
    rep(i,n) nxt[i] = i;
    function<int(int)> find = [&](int x) {
      if (x==n) return -1ll;
      return (nxt[x] == x) ? x : (nxt[x] = find(nxt[x]));
    };
  
    for (int x : order)
    {
      if (find(x)!=x) return make_pair(score, false);
      int a = find(x);
      int b = find(x+1);
      if (b==-1) return make_pair(score, false);
      score_from_construction += permuted[a] ^ permuted[b];
      nxt[a]=b;
    }

    if (score_from_construction != score) return make_pair(score, false);

    string trailing;
    if(sol >> trailing) return make_pair(score, false);
    return make_pair(score, true);
  };

  pair<ll, bool> judge_solved = check(judge_ans, judge_error);
  pair<ll, bool> author_solved = check(author_out, wrong_answer);

  if(!judge_solved.second)
    judge_error("NO! Judge solution does not provide construction leading to the answer");

  if (judge_solved.first < author_solved.first && author_solved.second)
    wrong_answer("NO! Author solution provides superior construction over judge");

  if (judge_solved.first != author_solved.first)
    wrong_answer("Author solution is inferior to judge");

  if(author_solved.second)
    accept_with_score(1);
  else
    accept_with_score(0.75);

}
