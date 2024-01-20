#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 105;

int n;

void solve() {
  std::cin >> n;
  std::cout << std::__lg(n - 1) + 1 << std::endl;
  for (int i = 0; i <= std::__lg(n - 1); i++) {
    std::vector<int> a;
    for (int j = 1; j <= n; j++) {
      if (j & (1 << i)) a.push_back(j);
    }
    std::cout << a.size() << " ";
    for (auto j : a) std::cout << j << " ";
    std::cout << std::endl;
  }

  std::string s;
  std::cin >> s;
  
  int ans = 0;
  for (unsigned i = 0; i < s.length(); i++) {
    if (s[i] == '1') ans += 1 << i;
  }
  if (!ans) ans = 1 << (std::__lg(n - 1) + 1);
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
