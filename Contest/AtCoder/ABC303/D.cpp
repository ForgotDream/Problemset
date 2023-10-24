#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int x, y, z;
  std::cin >> x >> y >> z;

  std::string s;
  std::cin >> s;

  int n = s.length();

  std::vector f(n + 1, std::vector<i64>(2));
  s = 'a' + s;
  f[0][0] = 0, f[0][1] = z;
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'a') {
      f[i][0] = std::min(f[i - 1][0] + x, f[i - 1][1] + z + x);
      f[i][1] = std::min(f[i - 1][1] + y, f[i - 1][0] + z + y);
    } else {
      f[i][0] = std::min(f[i - 1][0] + y, f[i - 1][1] + z + y);
      f[i][1] = std::min(f[i - 1][1] + x, f[i - 1][0] + z + x);
    }
  }

  std::cout << std::min(f[n][0], f[n][1]) << "\n";

  return 0;
}