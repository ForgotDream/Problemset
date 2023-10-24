#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<int> bucket(n + 1);
  for (int i = n - 1; i >= 0; i--) {
    if (bucket[std::max(0, i - a[i])]) {
      continue;
    }
    bucket[std::max(0, i - a[i])] = i;
  }

  int ans = 0, pre = 0;
  for (int i = bucket[0]; i < n;) {
    ans++;
    if (i + a[i] >= n - 1) {
      break;
    }
    int pivot = i;
    for (int j = pre; j < std::min(n, i + a[i] + 2); j++) {
      if (bucket[j] == 0) {
        continue;
      } else if (bucket[j] + a[bucket[j]] < pivot + a[pivot]) {
        continue;
      }
      pivot = bucket[j];
      pre = j;
    }
    i = pivot;
  }

  std::cout << ans << "\n";

  return 0;
}