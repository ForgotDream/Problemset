#include <bits/stdc++.h>

using i64 = long long;

struct BIT {
  int n;
  std::vector<i64> tree;
  BIT(int _n) {
    n = _n;
    tree.resize(n);
  }
  void add(int u, int val) {
    for (int i = u; i <= n; i += (i & -i)) {
      tree[i - 1] += val;
    }
  }
  i64 query(int u) {
    i64 res = 0;
    for (int i = u; i; i -= (i & -i)) {
      res += tree[i - 1];
    }
    return res;
  }
};

int main() {
  freopen("sort.in", "r", stdin);
  freopen("sort.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  auto calc = [](const std::vector<int> &a) -> i64 {
    auto b = a;
    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());

    i64 res = 0;
    BIT bit(b.size());
    for (int i = 0; i < a.size(); i++) {
      int cur = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
      res += bit.query(cur - 1);
      bit.add(cur, 1);
    }

    return res;
  };

  i64 ans = calc(a);
  std::reverse(a.begin(), a.end());
  ans = std::min(ans, calc(a));

  std::cout << ans << "\n";

  return 0;
}