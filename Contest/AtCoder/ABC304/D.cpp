#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int w, h, n;
  std::cin >> w >> h >> n;

  std::vector<int> p(n), q(n);
  for (int i = 0; i < n; i++) {
    std::cin >> p[i] >> q[i];
  }

  int A, B;
  std::cin >> A;
  std::vector<int> a(A);
  for (int i = 0; i < A; i++) {
    std::cin >> a[i];
  }
  a.push_back(w);

  std::cin >> B;
  std::vector<int> b(B);
  for (int i = 0; i < B; i++) {
    std::cin >> b[i];
  }
  b.push_back(h);

  std::map<int, std::map<int, int>> mp;
  i64 cnt = 0;
  for (int i = 0; i < n; i++) {
    auto xl = std::lower_bound(a.begin(), a.end(), p[i]);
    auto yl = std::lower_bound(b.begin(), b.end(), q[i]);

    mp[xl - a.begin()][yl - b.begin()]++;
    if (mp[xl - a.begin()][yl - b.begin()] == 1) {
      cnt++;
    }
  }

  int min = INT_MAX, max = 0;
  for (auto i : mp) {
    for (auto j : i.second) {
      min = std::min(min, j.second);
      max = std::max(max, j.second);
    }
  }

  if (cnt != 1ll * (A + 1) * (B + 1)) {
    min = 0;
  }
  std::cout << min << " " << max << "\n";

  return 0;
}