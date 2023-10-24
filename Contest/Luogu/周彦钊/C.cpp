#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> s(n);
  for (int i = 0; i < n; i++) {
    std::cin >> s[i];
  }

  std::sort(s.begin(), s.end());

  do {
    bool flg = true;
    for (int i = 0; i < n - 1; i++) {
      int cnt = 0;
      for (int j = 0; j < m; j++) {
        if (s[i][j] != s[i + 1][j]) {
          cnt++;
        }
      }
      if (cnt > 1) {
        flg = false;
        break;
      }
    }
    if (flg) {
      std::cout << "Yes\n";
      return 0;
    }
  } while (std::next_permutation(s.begin(), s.end()));

  std::cout << "No\n";

  return 0;
}