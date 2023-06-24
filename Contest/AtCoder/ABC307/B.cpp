#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::string> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  auto check = [&](std::string s) {
    int n = s.length();
    for (int i = 0; i < n; i++) {
      if (s[i] != s[n - i - 1]) {
        return false;
      }
    }
    return true;
  };

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (check(a[i] + a[j]) || check(a[j] + a[i])) {
        std::cout << "Yes\n";
        return 0;
      }
    }
  }
  std::cout << "No\n";

  return 0;
}