#include <bits/stdc++.h> // score: 100

using namespace std;
using ll = long long;
const int MAXN = 200200;
const int INF = 1e9;

int n;
int a[MAXN];
int p[MAXN];
ll d[MAXN];
bool used[MAXN];
vector<int> cycle;
vector<pair<int, int>> edges;

int c[MAXN];
int r[MAXN];

int dsu_get(int v) {
  return c[v] == v ? v : c[v] = dsu_get(c[v]);
}

int dsu_unite(int u, int v) {
  u = dsu_get(u);
  v = dsu_get(v);
  if (u == v) {
    return -1;
  }
  if (r[u] < r[v]) {
    swap(u, v);
  }
  c[v] = u;
  if (r[u] == r[v]) {
    ++r[u];
  }
  return u;
}

int f(int i, int j) {
  if (i == j) {
    return -INF;
  }
  return (a[i] ^ a[j]);
}

ll sum;

void kruskal(vector<pair<int,int>> e) {
  sort(e.begin(), e.end(), [&](auto x, auto y) {
    return f(x.first, x.second) > f(y.first, y.second);
  });
  int cnt = 0;
  for (auto [i, j] : e) {
    if (dsu_unite(i, j) != -1) {
      edges.push_back({i, j});
      sum += f(i, j);
      ++cnt;
    }
  }
  // printf("%d %d\n", cnt, e.size());
}

struct BinTrie {
  struct Node {
    int cnt;
    Node *to[2];
    unordered_set<int> ids;
    Node() {
      cnt = 0;
      to[0] = to[1] = nullptr;
    }
  };
  Node *root;
  BinTrie() {
    root = new Node();
  }
  void add(int id, int x) {
    Node *v = root;
    for (int i = 30; i >= 0; --i) {
      int b = (x >> i) & 1;
      if (v->to[b] == nullptr) {
        v->to[b] = new Node();
      }
      v = v->to[b];
      v->cnt++;
    }
    v->ids.insert(id);
  }
  void del(int id, int x) {
    Node *v = root;
    for (int i = 30; i >= 0; --i) {
      int b = (x >> i) & 1;
      v = v->to[b];
      v->cnt--;
    }
    v->ids.erase(id);
  }

  int get_best(int x) {
    Node *v = root;
    int res = 0;
    for (int i = 30; i >= 0; --i) {
      res <<= 1;
      int b = (x >> i) & 1;
      if (v->to[b ^ 1] != nullptr && v->to[b ^ 1]->cnt != 0) {
        v = v->to[b ^ 1];
        res += (b ^ 1);
      } else {
        v = v->to[b];
        res += b;
      }
    }

    return *v->ids.begin();
  }
};

BinTrie trie;

vector<int> comps[MAXN];
pair<int, int> best_comp[MAXN];

void relax_comp(int i, pair<int, int> edge) {
  auto best = best_comp[i];
  if (best.first != -1 || f(edge.first, edge.second) > f(best.first, best.second)) {
    best_comp[i] = edge;
  }
}

void greedy() {
  for (int i = 0; i < n; ++i) {
    c[i] = i;
    trie.add(i, a[i]);
    comps[i].push_back(i);
  }
  int it = 0;
  while (edges.size() != n - 1) {
    ++it;
    vector<pair<int,int>> e;
    for (int i = 0; i < n; ++i) {
      if (comps[i].empty()) {
        continue;
      }
      for (int v : comps[i]) {
        trie.del(v, a[v]);
      }
      pair<int, int> best_edge = {-1, -1};
      for (int v : comps[i]) {
        int u = trie.get_best(a[v]);
        if (dsu_get(v) != dsu_get(u)) {
          if (best_edge.first == -1 || f(u, v) > f(best_edge.first, best_edge.second)) {
            best_edge = {v, u};
          }
        }
      }
      if (best_edge.first != -1) {
        relax_comp(dsu_get(best_edge.first), best_edge);
        relax_comp(dsu_get(best_edge.second), best_edge);
      }
      for (int v : comps[i]) {
        trie.add(v, a[v]);
      }
    }
    for (int i = 0; i < n; ++i) {
      used[i] = false;
      if (best_comp[i].first != -1) {
        e.push_back(best_comp[i]);
      }
    }
    kruskal(e);
    for (int i = 0; i < n; ++i) {
      comps[i].clear();
      best_comp[i] = {-1, -1};
    }
    for (int i = 0; i < n; ++i) {
      comps[dsu_get(i)].push_back(i);
    }
  }
  // printf("%d\n", it);
  printf("%lld\n", sum);
}


struct GraphNode {
  int val;
  int ind, pow;
  GraphNode() {}
  GraphNode(int val, int ind, int pow) : val(val), ind(ind), pow(pow) {}

  // operator to compare the nodes:
  bool operator<(const GraphNode &other) const {
    if (pow == other.pow) {
      return ind < other.ind;
    }
    return pow < other.pow;
  }
};

vector<int> g[MAXN];
int vpow[MAXN];
vector<int> order;
bool removed[MAXN];
int new_ind[MAXN];

void dfs(int v, int p) {
  for (auto u: g[v]) {
    if (u == p) {
      continue;
    }
    dfs(u, v);
  }
  new_ind[v] = order.size();
  order.push_back(v);
}

void ordDfs(int v, int p) {
  reverse(g[v].begin(), g[v].end());
  for (auto u: g[v]) {
    if (u == p) {
      continue;
    }
    ordDfs(u, v);
  }
  if (p != -1)
    printf("%d ", new_ind[v]);
}

void print_ans() {
  for (auto e : edges) {
    g[e.first].push_back(e.second);
    g[e.second].push_back(e.first);
  }
  dfs(0, -1);
  for (int i = 0; i < n; ++i) {
    printf("%d ", order[i]);
  }
  printf("\n");
  ordDfs(0, -1);
  printf("\n");
}

void solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  greedy();
  print_ans();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
