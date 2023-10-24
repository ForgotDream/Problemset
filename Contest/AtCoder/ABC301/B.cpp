#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> a(n), b;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  b.push_back(a[0]);
  for (int i = 1; i < n; i++) {
    if (std::abs(a[i] - a[i - 1]) != 1) {
      if (a[i - 1] < a[i]) {
        for (int j = a[i - 1] + 1; j < a[i]; j++) {
          b.push_back(j);
        }
      } else {
        for (int j = a[i - 1] - 1; j > a[i]; j--) {
          b.push_back(j);
        }
      }
    }
    b.push_back(a[i]);
  }

  for (int i = 0; i < b.size(); i++) {
    std::cout << b[i] << " \n"[i == b.size() - 1];
  }

  return 0;
}