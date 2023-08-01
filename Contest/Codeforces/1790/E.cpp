#include <bits/stdc++.h>

using i64 = long long;

struct Node {
  int l, r;
  Node() = default;
  Node(int _l, int _r) : l(_l), r(_r) {} 
  bool operator<(const Node &rhs) const { return l < rhs.l; }
};

void solve() {
  int x;
  std::cin >> x;

  int len = 0, cpy = x;
  for (; cpy; cpy >>= 1, len++);

  std::multiset<int> pre, aft;
  std::function<void(int, int)> dfs1 = [&](int idx, int cur) {
    if (idx == len / 2 + 1) {
      pre.insert(cur);
      return;
    }
    if (x & (1 << cur)) dfs1(idx + 1, cur + (1 << idx));
    dfs1(idx + 1, cur);
  };
  std::function<void(int, int)> dfs2 = [&](int idx, int cur) {
    if (idx == len + 1) {
      aft.insert(cur);
      return;
    }
    if (x & (1 << cur)) dfs2(idx + 1, cur + (1 << idx));
    dfs2(idx + 1, cur);
  };

  dfs1(0, 0), dfs2(len / 2 + 1, 0);

}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}