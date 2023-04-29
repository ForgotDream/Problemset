#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  std::vector<bool> vis(n, false);
  for (auto &i : a) {
    std::cin >> i;
  }

  for (int i = 0; i < n; i++) {
    if (vis[i]) {
      continue;
    } else {
      vis[a[i] - 1] = true;
    }
  }

  int ans = 0;
  std::vector<int> vec;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      ans++;
      vec.push_back(i + 1);
    }
  }

  std::cout << ans << "\n";
  for (auto i : vec) {
    std::cout << i << " ";
  }

  return 0;
}