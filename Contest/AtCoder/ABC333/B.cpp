#include <bits/stdc++.h>

using i64 = long long;

char c[4];
int calc(char a, char b) {
  return std::min((a - b + 5) % 5, (b - a + 5) % 5);
}
void solve() {
  for (auto &i : c) std::cin >> i;
  if (calc(c[0], c[1]) == calc(c[2], c[3])) std::cout << "Yes\n";
  else std::cout << "No\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
