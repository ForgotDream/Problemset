#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<int> a(n), d(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector bucket(n + 1, std::vector<int>());
  for (int i = n - 1; i >= 0; i--) {
    bucket[std::max(0, i - a[i])].push_back(i);
  }

  int ans = 0, pre = 0;
  for (int i = bucket[0][0]; i < n;) {
    ans++;
    if (i + a[i] >= n - 1) {
      break;
    }
    int pivot = i;
    for (int j = pre; j < std::min(n, i + a[i] + 2); j++) {
      if (bucket[j].empty()) {
        continue;
      } else if (bucket[j][0] + a[bucket[j][0]] < pivot + a[pivot]) {
        continue;
      }
      pivot = bucket[j][0];
      pre = j;
    }
    i = pivot;
  }

  std::cout << ans << "\n";

  return 0;
}