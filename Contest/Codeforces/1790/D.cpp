#include <bits/stdc++.h>

using i64 = long long;

struct Node {
  int l, r;
  Node() = default;
  Node(int _l, int _r) : l(_l), r(_r) {} 
  bool operator<(const Node &rhs) const { return l < rhs.l; }
};

void solve() {
  int n;
  std::cin >> n;
  
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  std::sort(a.begin(), a.end());

  auto b = a;
  for (auto i : b) {
    b.push_back(i + 1);
  }
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());

  int m = b.size();
  std::vector<int> cnt(m);
  std::vector bln(m + 1, std::vector<int>());
  for (auto i : a) {
    auto it = std::lower_bound(b.begin(), b.end(), i);
    int cur = it - b.begin();
    cnt[cur]++;
  }
  for (auto i : a)  {
    auto it = std::lower_bound(b.begin(), b.end(), i);
    int cur = it - b.begin();
    if (bln[cnt[cur]].empty() || bln[cnt[cur]].back() != cur) {
      bln[cnt[cur]].push_back(cur);
    }
  }
  int ans = 0;

  std::set<Node> tree;

  auto split = [&](int idx) {
    auto it = tree.lower_bound(Node(idx, 0));
    if (it != tree.end() && it->l == idx) {
      return it;
    }
    it--;
    auto [l, r] = *it;
    tree.erase(it);
    tree.insert(Node(l, idx - 1));
    return tree.insert(Node(idx, r)).first;
  };

  auto erase = [&](int val) {
    auto end = split(val + 1), begin = split(val);
    tree.erase(begin, end);
  };

  tree.emplace(0, m - 1);
  for (int i = 1; i <= m; i++) {
    for (auto j : bln[i - 1]) {
      // std::cerr << j << " ";
      erase(j);
    }
    ans += tree.size();
    if (tree.empty()) {
      break;
    }
  }
  std::cout << ans << "\n";
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