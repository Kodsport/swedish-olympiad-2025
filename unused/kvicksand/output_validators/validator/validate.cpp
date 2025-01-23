#include "validate.h"
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

vi BFS(vector<vi> &graph, vi &sand){
    vi D2(sz(graph), -1);
    vector<int> seen(sz(graph), 0);
    queue<int> Q;
    Q.push(0);
    D2[0] = 0;
    while(!Q.empty()){
        int a = Q.front();
        Q.pop();
        if(!seen[a]){
            seen[a] = 1;
            if(sand[a] == 0){
                for(auto b : graph[a]){
                    if(D2[b] == -1){
                        D2[b] = D2[a]+1;
                        Q.push(b);
                    }
                }
            }
        }
    }
    return D2;
}

int main(int argc, char **argv) {
  init_io(argc, argv);

  int n, m;
  judge_in >> n >> m;
  vi D(n);
  for(int c1 = 0; c1 < n; c1++){
    judge_in >> D[c1];
  }

  vector<vi> graph(n, vi());
  for(int c1 = 0; c1 < m; c1++){
    int a,b;
    judge_in >> a >> b;
    a--;
    b--;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  vi sand;

  int contestant1;
  if(!(author_out >> contestant1)){
    wrong_answer("Could not read first number");
  }
  if(contestant1 < -1 || contestant1 > n)wrong_answer("First number out of range");

  int judge1;
  judge_ans >> judge1;

  if(contestant1 == -1){
    if(judge1 != -1){
      wrong_answer("Contestant said -1 but answer existed");
    }
  }
  else{
    vi sand(n, 0);
    for(int c1 = 0; c1 < contestant1; c1++){
      int a;
      if(!(author_out >> a)){
        wrong_answer("Could not read %dth number", c1+1);
      }
      if(a <= 0 || a > n){
        wrong_answer("%dth number out of range (%d)", c1+1, a);
      }
      a--;
      sand[a] = 1;
    }

    vi D2 = BFS(graph, sand);

    rep(c1,0,n){
      if(D[c1] != D2[c1]){
        wrong_answer("Sand gave wrong distances, d[%d] was %d instead of %d", c1+1, D2[c1], D[c1]);
      }
    }

    if(judge1 == -1){
      judge_error("Judge said -1 but contestant found solution");
    }

  }
  string trailing;
  if(author_out >> trailing){
    wrong_answer("Trailing output");
  }

  accept();
}
