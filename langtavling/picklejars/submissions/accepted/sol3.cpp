#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define DEBUG 0

using namespace std;

struct TrieNode {
  // in the leaves: repetition count minus 1.
  int child[2];
};

struct Trie {
  std::vector<int> deleted_node_pos;
  std::vector<TrieNode> nodes;
  int depth = 0;
  Trie(long long maxA) {
    nodes.push_back(TrieNode{-1, -1});
    depth = maxA == 0 ? 63 : 63 - __builtin_clzll(maxA);
#if DEBUG
    fprintf(stderr, "depth: %d\n", depth);
#endif
  }

  int new_node() {
    if (deleted_node_pos.empty()) {
      nodes.push_back(TrieNode{-1, -1});
      return nodes.size() - 1;
    }
    int ans = deleted_node_pos.back();
    deleted_node_pos.pop_back();
    return ans;
  }
  void remove_node(int pos) {
    nodes[pos].child[0] = nodes[pos].child[1] = -1;
    deleted_node_pos.push_back(pos);
  }

  void insert(long long val) {
    int node = 0;
    for (int b = depth; b > 0; b--) {
      int c = (val & (1ll << b)) == 0 ? 0 : 1;
      if (nodes[node].child[c] == -1) {
        nodes[node].child[c] = new_node();
      }
      node = nodes[node].child[c];
    }
    nodes[node].child[val & 1] += 1;
  }

  bool erase(int node, int depth, long long val) {
    if (node == -1) {
      return true;
    }
    int c = (val & (1ll << depth)) == 0 ? 0 : 1;
    if (depth == 0) {
      nodes[node].child[c] -= 1;
    } else if (erase(nodes[node].child[c], depth - 1, val)) {
      nodes[node].child[c] = -1;
    }
    if (nodes[node].child[0] == -1 && nodes[node].child[1] == -1) {
      remove_node(node);
      return true;
    }
    return false;
  }

  void erase(long long val) { erase(0, depth, val); }

  long long max_xor_element(long long val) {
    int node = 0;
    long long vv = 0;
    for (int b = depth; b >= 0; b--) {
      int c = (val & (1ll << b)) == 0 ? 0 : 1;
      if (nodes[node].child[c ^ 1] != -1) {
        c = c ^ 1;
      }
      node = nodes[node].child[c];
      vv = vv * 2 + c;
    }
    return vv;
  }
};

pair<long long, vector<vector<int>>> solve(int N, vector<long long> A) {
  Trie trie(*std::max_element(A.begin(), A.end()));
  for (int i = 0; i < N; i++) {
    trie.insert(A[i]);
  }

  std::unordered_map<long long, std::unordered_set<int>> v_to_indices;

  for (int i = 0; i < N; i++) {
    v_to_indices[A[i]].insert(i);
  }

#if DEBUG
  for (int i = 0; i < trie.nodes.size(); i++) {
    fprintf(stderr, "%d %d\n", trie.nodes[i].child[0], trie.nodes[i].child[1]);
  }

  for (int a : A) {
    fprintf(stderr, "%x ", a);
  }
  fprintf(stderr, "\n");
#endif

  long long ans = 0;

  std::vector<int> cc_of(N);
  for (size_t i = 0; i < N; i++) {
    cc_of[i] = i;
  }

  std::vector<std::vector<int>> ccs(N);
  for (int i = 0; i < N; i++) {
    ccs[i].push_back(i);
  }

  std::vector<std::vector<int>> ccs_by_size(N + 1);
  for (int i = 0; i < N; i++) {
    ccs_by_size[1].push_back(i);
  }
  vector<vector<int>> g(N);
  for (int i = 0; i < N; i++) {
    for (int cc : ccs_by_size[i]) {
      // this CC might have been merged with since being inserted in
      // `ccs_by_size`.
      if (ccs[cc].size() != i) {
        continue;
      }
      std::vector<int> cc_copy = ccs[cc];
      // remove elements of this CC
      for (int el : ccs[cc]) {
#if DEBUG
        fprintf(stderr, "remove %d (%x)\n", el, A[el]);
#endif
        trie.erase(A[el]);
        v_to_indices[A[el]].erase(el);
      }
#if DEBUG
      for (int i = 0; i < trie.nodes.size(); i++) {
        fprintf(stderr, "%d %d\n", trie.nodes[i].child[0],
                trie.nodes[i].child[1]);
      }
#endif

      // find the best edge from this cc to not-this-cc.
      int best_el = ccs[cc][0];
      int best_other = ccs[cc][0];
      for (int el : ccs[cc]) {
        long long oth_val = trie.max_xor_element(A[el]);
        int oth = *v_to_indices[oth_val].begin();
#if DEBUG
        fprintf(stderr, "bst %d: %d %x\n", el, oth, A[el] ^ A[oth]);
#endif
        assert(A[oth] == oth_val);
        if ((A[el] ^ A[oth]) >= (A[best_el] ^ A[best_other])) {
          best_el = el;
          best_other = oth;
        }
      }
      g[best_el].push_back(best_other);
      g[best_other].push_back(best_el);
      long long edgev = A[best_el] ^ A[best_other];
      ans += edgev;

#if DEBUG
      fprintf(stderr, "best: %d %d %x\n", best_el, best_other, edgev);

      for (int el : ccs[cc]) {
        for (int o = 0; o < N; o++) {
          if (cc_of[o] != cc) {
            fprintf(stderr, "cmp %d %d %x\n", el, o, A[el] ^ A[o]);
            assert((A[el] ^ A[o]) <= edgev);
          }
        }
      }
#endif

      assert(cc_of[best_el] == cc);
      assert(cc_of[best_other] != cc);

      best_other = cc_of[best_other];
      best_el = cc_of[best_el];

      // Merge the two CCs.
      if (ccs[best_el].size() > ccs[best_other].size()) {
        std::swap(best_el, best_other);
      }
      ccs[best_other].reserve(ccs[best_other].size() + ccs[best_el].size());
      for (auto v : ccs[best_el]) {
        ccs[best_other].push_back(v);
        cc_of[v] = best_other;
      }
      ccs[best_el].clear();

      ccs_by_size[ccs[best_other].size()].push_back(best_other);

      // add the CC back
      for (int el : cc_copy) {
        trie.insert(A[el]);
        v_to_indices[A[el]].insert(el);
      }
#if DEBUG
      for (int i = 0; i < trie.nodes.size(); i++) {
        fprintf(stderr, "%d %d\n", trie.nodes[i].child[0],
                trie.nodes[i].child[1]);
      }
#endif
    }
  }
  assert(ccs_by_size[N].size() == 1);
  return {ans, g};
}

void dfs(int v, int p, vector<vector<int>> &g, vector<int> &order,
         vector<int> &new_ind) {
  for (auto u : g[v]) {
    if (u == p) {
      continue;
    }
    dfs(u, v, g, order, new_ind);
  }
  new_ind[v] = order.size();
  order.push_back(v);
}

void ordDfs(int v, int p, vector<vector<int>> &g, vector<int> &new_ind) {
  reverse(g[v].begin(), g[v].end());
  for (auto u : g[v]) {
    if (u == p) {
      continue;
    }
    ordDfs(u, v, g, new_ind);
  }
  if (p != -1)
    cout << new_ind[v] << " ";
}

void print_ans(vector<vector<int>> &g) {
  vector<int> order, new_ind(g.size());
  dfs(0, -1, g, order, new_ind);
  for (auto e : order) {
    cout << e << " ";
  }
  cout << "\n";
  ordDfs(0, -1, g, new_ind);
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<long long> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  auto [we, g] = solve(N, A);
  cout << we << "\n";
  print_ans(g);
  return 0;
}
