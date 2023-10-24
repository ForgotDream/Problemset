#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> x(k), c(k);
  for (int i = 0; i < k; i++) {
    std::cin >> x[i];
  }
  for (int i = 0; i < k; i++) {
    std::cin >> c[i];
  }

  for (int i = 0; i < k; i++) {
    if (x[i] < c[i]) {
      std::cout << "NO\n";
      return;
    }
  }

  std::string ans = "";
  for (int i = 0; i < k; i++) {
    for (int i = 0; i < c[i] - 3; i++) {
      ans += (i + 'a');
    }
    char ch = i + 'a';
    std::string tmp = "xy";
    tmp += ch;
    if (((x[i] - (c[i] - 3)) % 3) != 0) {
      std::cout << "NO\n";
      return;
    }
    for (int i = 0; i < ((x[i] - (c[i] - 3)) / 3); i++) {
      ans += tmp;
    }
  }

  std::cout << "YES\n";  
  std::cout << ans << "\n";

  return;
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