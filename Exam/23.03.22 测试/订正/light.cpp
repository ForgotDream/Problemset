#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, r, g;
  std::cin >> n >> r >> g;

  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }

  if (r + g >= n) {
    std::cout << 1 << "\n";
    return 0;
  }

  std::sort(a.begin() + 1, a.end());

  auto check = [&](int num) -> bool {
    std::vector<std::vector<int>> f(r + 1, std::vector<int>(g + 1));
    std::vector<int> p(n + 2), q(n + 2);
    
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (a[j] - a[i] + 1 <= num) {
          p[i] = j;
        }
        if (a[j] - a[i] + 1 <= 2 * num) {
          q[i] = j;
        }
      }
    }

    p[n + 1] = q[n + 1] = n;

    for (int i = 0; i <= r; i++) {
      for (int j = 0; j <= g; j++) {
        if (i > 0) {
          f[i][j] = std::max(f[i][j], p[f[i - 1][j] + 1]);
        }
        if (j > 0) {
          f[i][j] = std::max(f[i][j], q[f[i][j - 1] + 1]);
        }
      }
    }

    return f[r][g] == n;
  };

  int L = 1, R = a[n] - a[1], ans = 0;

  while (L <= R) {
    int mid = (L + R) >> 1;
    if (check(mid)) {
      ans = mid;
      R = mid - 1;
    } else {
      L = mid + 1;
    }
  }

  std::cout << ans << "\n";

  return 0;
}