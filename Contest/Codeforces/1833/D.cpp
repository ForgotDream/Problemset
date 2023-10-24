#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  int p1, p2;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    if (a[i] == n) {
      p1 = i;
    } else if (a[i] == n - 1) {
      p2 = i;
    }
  }

  if (n == 1) {
    std::cout << 1 << "\n";
    return;
  }

  auto calc = [&](int u) {
    for (int i = u; i < n; i++) {
      std::cout << a[i] << " ";
    }

    if (u == n - 1) {
      if (a[0] > a[u - 1]) {
        for (int i = 0; i < u; i++) {
          std::cout << a[i] << " ";
        }
      } else {
        int p = -1;
        for (int i = u - 1; i >= 0; i--) {
          if (a[i] < a[0]) {
            p = i;
            break;
          }
          std::cout << a[i] << " ";
        }
        for (int i = 0; i <= p; i++) {
          std::cout << a[i] << " ";
        }
      }
      std::cout << "\n";
      return;
    }

    std::cout << a[u - 1] << " ";
    if (a[0] > a[u - 2]) {
        for (int i = 0; i < u - 1; i++) {
          std::cout << a[i] << " ";
        }
      } else {
        int p = -1;
        for (int i = u - 2; i >= 0; i--) {
          if (a[i] < a[0]) {
            p = i;
            break;
          }
          std::cout << a[i] << " ";
        }
        for (int i = 0; i <= p; i++) {
          std::cout << a[i] << " ";
        }
      }

    std::cout << "\n";
  };

  if (p1 == 0) {
    calc(p2);
  } else {
    calc(p1);
  }

}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}