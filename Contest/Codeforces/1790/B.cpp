#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, s, r;
  std::cin >> n >> s >> r;

  std::vector f(n, std::vector<int>(r + 1));
  f[0][0] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= r; j++) {
      for (int k = 1; k <= std::min(j, s - r); k++) {
        if (f[i - 1][j - k]) f[i][j] += f[i - 1][j - k];
      }
    }
  }
  std::vector<int> ans = {s - r};
  int cur = r;
  for (int i = n - 1; i >= 1; i--) {
    for (int j = 1; j <= std::min(cur, s - r); j++) {
      if (f[i - 1][cur - j]) {
        cur -= j, ans.push_back(j);
        break;
      }
    }
  }
  for (auto i : ans) {
    std::cout << i << " ";
  }
  std::cout << "\n";
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