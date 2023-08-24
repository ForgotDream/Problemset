#include <iostream>

using i64 = long long;

i64 n;

int main() {
  std::freopen("au.in", "r", stdin);
  std::freopen("au.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;

  int ans = 0, p = 0;
  for (int k = 1; k <= n; k++) {
    int cpy = k;
    i64 all = 1;
    for (int i = 2; i * i <= cpy; i++) {
      if (cpy % i == 0) {
        int cnt = 1;
        while (cpy % i == 0)  cpy /= i, cnt++;
        all *= cnt;
      }
    }
    if (all > p) ans = k, p = all;
  }
  std::cout << ans << "\n";

  return 0;
}