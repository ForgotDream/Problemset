#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, a, b;
  std::cin >> n >> a >> b;

  std::vector<int> c(n);
  for (int i = 0; i < n; i++) {
    std::cin >> c[i];
    if (c[i] == a + b) {
      std::cout << i + 1 << "\n";
      return 0;
    }
  }

  return 0;
}