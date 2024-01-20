#include <bits/stdc++.h>

using i64 = long long;

std::string s;

void solve() {
  std::cin >> s;

  unsigned p = 0;
  while (p < s.length() && s[p] == 'A') p++;
  while (p < s.length() && s[p] == 'B') p++;
  while (p < s.length() && s[p] == 'C') p++;

  if (p != s.length()) std::cout << "No\n";
  else std::cout << "Yes\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
