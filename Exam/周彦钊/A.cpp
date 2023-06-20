#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::string s;
  std::cin >> n >> s;

  std::string t;
  for (int i = 0; i < n; i++) { t += s[i], t += s[i]; }
  std::cout << t << "\n";

  return 0;
}