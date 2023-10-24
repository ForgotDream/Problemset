#include <atcoder/modint.hpp>
#include <bits/stdc++.h>

using i64 = long long;
using Z = atcoder::modint998244353;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;
  int n = s.length();

  if (n & 1) {
    std::cout << 0 << "\n";
    return 0;
  }

  std::vector f(n, std::vector<Z>(n + 1));
  if (s[0] == '(' || s[0] == '?') {
    f[0][1] = 1;
  } else {
    std::cout << 0 << "\n";
    return 0;
  }
  for (int i = 1; i < n; i++) {
    if (s[i] == '(') {
      for (int j = 0; j < n; j++) {
        f[i][j + 1] = f[i - 1][j];
      }
    } else if (s[i] == ')') {
      for (int j = 1; j <= n; j++) {
        f[i][j - 1] = f[i - 1][j];
      }
    } else {
      for (int j = 0; j <= n; j++) {
        if (j != 0) {
          f[i][j] += f[i - 1][j - 1];
        }
        if (j != n) {
          f[i][j] += f[i - 1][j + 1];
        }
      }
    }
  }

  std::cout << f[n - 1][0].val() << "\n";

  return 0;
}