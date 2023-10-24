#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> a(3 * n);
  for (int i = 0; i < 3 * n; i++) { std::cin >> a[i], a[i]--; }

  std::vector<int> bucket(3 * n, -1), t(n);
  for (int i = 0; i < 3 * n; i++) {
    t[a[i]]++;
    if (t[a[i]] == 2) { bucket[i] = a[i]; }
  }

  for (int i = 0; i < 3 * n; i++) {
    if (~bucket[i]) { std::cout << bucket[i] + 1 << " \n"[i == 3 * n - 1]; }
  }

  return 0;
}