#include <bits/stdc++.h>
using namespace std;

#define int int64_t

using Iter = vector<pair<int, int>>::iterator;

int log2(int a) {
  return CHAR_BIT * sizeof(unsigned long long) - __builtin_clzll(a) - 1;
}
int relevant_bit(Iter first, Iter last) {
  if (first == last) return -1;
  int x = first->first ^ prev(last)->first;
  return x == 0 ? -1 : log2(x);
}

vector<pair<int, int>> v;
vector<vector<int>> g;
void add(Iter a, Iter b) {
  int x = a->second;
  int y = b->second;
  g[x].push_back(y);
  g[y].push_back(x);
}

void add_arbitrarily(Iter a_first, Iter a_last, Iter b_first, Iter b_last) {
  if (a_first == a_last || b_first == b_last) return;
  for (auto a = a_first; a != a_last; ++a)
    add(a, b_first);
  for (auto b = b_first; b != b_last; ++b)
    if (b != b_first)
      add(a_first, b);
}

bool bit_can_partition(Iter first, Iter last, int bit) {
  array<int, 2> cnt{0, 0};
  auto has_bit = [bit](pair<int, int> const& x) { return (x.first & ((int)1 << bit)) != 0; };
  for (auto it = first; it != last; ++it)
    cnt[has_bit(*it)]++;
  return cnt[0] && cnt[1];
}

tuple<int, Iter, Iter> best_cross(Iter a_first, Iter a_last, Iter b_first, Iter b_last, int bit) {
  if (a_first == a_last || b_first == b_last)
    return {-1, a_first, b_first};

  if (bit == -1 || (a_last - a_first == 1 && b_last - b_first == 1))
    return {a_first->first ^ b_first->first, a_first, b_first};

  auto has_bit = [bit](pair<int, int> const& x) { return (x.first & ((int)1 << bit)) != 0; };
  bool a_split = bit_can_partition(a_first, a_last, bit);
  bool b_split = bit_can_partition(b_first, b_last, bit);
  if (!a_split && !b_split)
    return best_cross(a_first, a_last, b_first, b_last, bit-1);

  if (!a_split) {
    Iter b_mid = partition(b_first, b_last, has_bit);
    auto ans_1 = best_cross(a_first, a_last, b_mid, b_last, bit-1);
    auto ans_2 = best_cross(a_first, a_last, b_first, b_mid, bit-1);
    return max(ans_1, ans_2);
  }
  if (!b_split) {
    Iter a_mid = partition(a_first, a_last, has_bit);
    auto ans_1 = best_cross(a_first, a_mid, b_first, b_last, bit-1);
    auto ans_2 = best_cross(a_mid, a_last, b_first, b_last, bit-1);
    return max(ans_1, ans_2);
  }
  Iter a_mid = partition(a_first, a_last, has_bit);
  Iter b_mid = partition(b_first, b_last, has_bit);
  auto ans_1 = best_cross(a_first, a_mid, b_mid, b_last, bit-1);
  auto ans_2 = best_cross(a_mid, a_last, b_first, b_mid, bit-1);
  return max(ans_1, ans_2);
}

void connect_left(Iter a_first, Iter a_last, Iter b_first, Iter b_last, int bit) {
  if (a_first == a_last || b_first == b_last) return;

  if (bit == -1 || b_last - b_first == 1) {
    for (auto a = a_first; a != a_last; ++a)
      add(a, b_first);
    return;
  }

  auto has_bit = [bit](pair<int, int> const& x) { return (x.first & ((int)1 << bit)) != 0; };
  bool b_split = bit_can_partition(b_first, b_last, bit);
  if (!b_split) {
    connect_left(a_first, a_last, b_first, b_last, bit-1);
    return;
  }

  Iter a_mid = partition(a_first, a_last, has_bit);
  Iter b_mid = partition(b_first, b_last, has_bit);
  connect_left(a_first, a_mid, b_mid, b_last, bit-1);
  connect_left(a_mid, a_last, b_first, b_mid, bit-1);
}

void solve(Iter a_first, Iter a_last, Iter b_first, Iter b_last, int bit) {
  assert(a_first != a_last);
  assert(b_first != b_last);

  if (a_first == a_last || b_first == b_last) return;
  if (bit == -1 || a_last - a_first == 1 || b_last - b_first == 1) {
    add_arbitrarily(a_first, a_last, b_first, b_last);
    return;
  }
  auto has_bit = [bit](pair<int, int> const& x) { return (x.first & ((int)1 << bit)) != 0; };
  bool a_split = bit_can_partition(a_first, a_last, bit);
  bool b_split = bit_can_partition(b_first, b_last, bit);
  if (!a_split && !b_split) {
    solve(a_first, a_last, b_first, b_last, bit-1);
    return;
  }
  bool need_cross = true;
  Iter a_mid = partition(a_first, a_last, has_bit);
  Iter b_mid = partition(b_first, b_last, has_bit);
  if (a_first == a_mid)
    { connect_left(b_mid, b_last, a_first, a_last, bit-1); need_cross = false; }
  else if (b_mid == b_last)
    { connect_left(a_first, a_mid, b_first, b_last, bit-1); need_cross = false; }
  else
    solve(a_first, a_mid, b_mid, b_last, bit-1);

  if (a_mid == a_last)
    { connect_left(b_first, b_mid, a_first, a_last, bit-1); need_cross = false; }
  else if (b_first == b_mid)
    { connect_left(a_mid, a_last, b_first, b_last, bit-1); need_cross = false; }
  else
    solve(a_mid, a_last, b_first, b_mid, bit-1);

  if (need_cross) {
    auto cross1 = best_cross(a_first, a_mid, b_first, b_mid, bit-1);
    auto cross2 = best_cross(a_mid, a_last, b_mid, b_last, bit-1);
    auto cross = max(cross1, cross2);
    add(get<1>(cross), get<2>(cross));
  }
}

signed main() {
  ios::sync_with_stdio(false);
  int n; cin >> n;
  vector<int> v_orig;
  for (int i=0; i<n; ++i) {
    int x; cin >> x;
    v.emplace_back(x, i);
    v_orig.push_back(x);
  }
  sort(v.begin(), v.end());
  g.resize(n);

  int last_bit = relevant_bit(v.begin(), v.end());
  if (last_bit == -1) {
    add_arbitrarily(v.begin(), v.begin()+1, v.begin()+1, v.end());
  } else {
    Iter mid = partition(v.begin(), v.end(), [&](pair<int, int> const& p) { return (p.first&((int)1 << last_bit)) != 0; });
    solve(v.begin(), mid, mid, v.end(), last_bit);
  }

  vector<int> order;
  vector<int> collisions;
  auto dfs = [&](auto&& self, int x, int p) -> int {
    int cost = 0;
    int dfs_index = order.size();
    order.push_back(x);
    for (auto y : g[x]) {
      if (y == p) continue;
      cost += self(self, y, x);
      cost += v_orig[x] ^ v_orig[y];
    }
    collisions.push_back(dfs_index);
    return cost;
  };

  int cost = dfs(dfs, 0, -1);
  cout << cost << '\n';
  copy(order.rbegin(), order.rend(), ostream_iterator<int>(cout, " "));
  cout << '\n';
  collisions.pop_back();
  for (int i=0; i<(int)collisions.size(); ++i)
    cout << (n - 1) - collisions[i] << ' ';
  cout << '\n';
}
